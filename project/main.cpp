#include "sweeper.h"
#include <wx/wx.h>
#include <wx/image.h>
#include <wx/numdlg.h>
#include <wx/spinctrl.h>
#include <wx/msgdlg.h>
#include <vector>
#include <map>

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame {
public:
    MyFrame(const wxString& title, const wxPoint& pos, int rows, int cols, int mines);

private:
    void OnLeftClick(wxMouseEvent& event);
    void OnRightClick(wxMouseEvent& event);
    void UpdateTileImage(int row, int col);
    void DrawVisibleField(const field& plot);
    void OnTimerUpdate(wxTimerEvent&);
    void UpdateFlagCount();
    // Header definitions
    wxStaticText* flagTopText_;
    wxStaticText* flagCountText_;
    wxStaticText* timerTopText_;
    wxStaticText* timerText_;
    wxTimer* timer_;
    int elapsedSeconds_ = 0;
    // Global game definitions
    std::map<wxWindowID, std::pair<int, int>> idToGridCoord;
    std::vector<std::vector<wxStaticBitmap*>> tiles;
    int gridRows_; // Number of rows
    int gridCols_; // Number of columns
    int gridMines_; // Number of mines
    wxBitmap tileBitmap_;
    wxBitmap cTileBitmap_;
    field* g_field = new field();
    bool g_gameStarted = false; // Check for game started
    bool g_gameOver = false; // Check for game over
    int tileSize = 32; // Pixel size of tiles
};

// User input for grid size and mine count
class GridSetupDialog : public wxDialog {
public:
    GridSetupDialog(wxWindow* parent)
        : wxDialog(parent, wxID_ANY, "Game initiation", wxDefaultPosition, wxDefaultSize) {
        // Create a flexible grid sizer
        wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
        wxFlexGridSizer* gridSizer = new wxFlexGridSizer(2, 5, 5);
        // Rows
        gridSizer->Add(new wxStaticText(this, wxID_ANY, "Rows (MAX 50):"), 0, wxALIGN_CENTER_VERTICAL);
        rowsSpin_ = new wxSpinCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 50, 10);
        gridSizer->Add(rowsSpin_);
        // Columns
        gridSizer->Add(new wxStaticText(this, wxID_ANY, "Columns (MAX 80):"), 0, wxALIGN_CENTER_VERTICAL);
        colsSpin_ = new wxSpinCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 80, 10);
        gridSizer->Add(colsSpin_);
        // Mines
        mineLabel_ = new wxStaticText(this, wxID_ANY, "Mines (MAX 80):");  // default value
        gridSizer->Add(mineLabel_, 0, wxALIGN_CENTER_VERTICAL);
        minesSpin_ = new wxSpinCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 800, 10);
        gridSizer->Add(minesSpin_);
        // Add the grid sizer
        mainSizer->Add(gridSizer, 1, wxALL | wxEXPAND, 10);
        // Create a horizontal sizer to hold OK and Cancel buttons
        wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
        btnSizer->AddStretchSpacer();
        btnSizer->Add(new wxButton(this, wxID_OK), 0, wxALL, 5);
        btnSizer->Add(new wxButton(this, wxID_CANCEL), 0, wxALL, 5);
        mainSizer->Add(btnSizer, 0, wxEXPAND | wxRIGHT | wxBOTTOM, 5);
        SetSizerAndFit(mainSizer);
        // Bind change events to update mine limit dynamically
        rowsSpin_->Bind(wxEVT_SPINCTRL, &GridSetupDialog::OnGridSizeChanged, this);
        colsSpin_->Bind(wxEVT_SPINCTRL, &GridSetupDialog::OnGridSizeChanged, this);
        // Set initial max mine value based on current grid size
        AdjustMineLimit();
    }
    int GetRows() const { return rowsSpin_->GetValue(); }
    int GetCols() const { return colsSpin_->GetValue(); }
    int GetMines() const { return minesSpin_->GetValue(); }

private:
    wxSpinCtrl* rowsSpin_;
    wxSpinCtrl* colsSpin_;
    wxSpinCtrl* minesSpin_;
    wxStaticText* mineLabel_;
    // Adjusting mine limit if the grid size has been changed
    void OnGridSizeChanged(wxCommandEvent&) {
        AdjustMineLimit();
    }
    // Updating maximum mine count so it doesn't exceed 80% of tiles
    void AdjustMineLimit() {
        int rows = rowsSpin_->GetValue();
        int cols = colsSpin_->GetValue();
        int maxMines = std::max(1, (rows * cols * 80) / 100);  // 80% cap
        // Update mine spin range and reset if needed
        int currentMines = minesSpin_->GetValue();
        minesSpin_->SetRange(1, maxMines);
        if (currentMines > maxMines) minesSpin_->SetValue(maxMines);
        // Update the label text
        mineLabel_->SetLabel(wxString::Format("Mines (MAX %d):", maxMines));
        Layout(); // Ensure UI updates properly
    }
};

wxIMPLEMENT_APP(MyApp);

// Game initiation
bool MyApp::OnInit() {
    wxInitAllImageHandlers();
    // Create and show the setup dialog
    GridSetupDialog dlg(NULL);
    if(dlg.ShowModal() != wxID_OK) return false;
    // Retrieve user-selected settings from the dialog
    int rows = dlg.GetRows();
    int cols = dlg.GetCols();
    int mines = dlg.GetMines();
    // Create the main application window with the selected configuration
    MyFrame* frame = new MyFrame("Minesweeper", wxDefaultPosition, rows, cols, mines);
    frame->Show(true);
    return true;
}

// Main
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, int rows, int cols, int mines)    
    : wxFrame(NULL, wxID_ANY, title, pos), gridRows_(rows), gridCols_(cols), gridMines_(mines) {
    // Changing size of tiles according to grid size
    if (rows > 30 || cols > 50) tileSize = 16;
    else if (rows <= 7 && cols <= 12) tileSize = 128;
    else if (rows <= 14 && cols <= 24) tileSize = 64;
    // Creating main panel
    wxPanel* mainPanel = new wxPanel(this);
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
    // Create the top panel (header)
    wxPanel* topBar = new wxPanel(mainPanel, wxID_ANY, wxDefaultPosition, wxSize(-1, 80));
    topBar->SetBackgroundColour(wxColour(161, 161, 161)); // Light gray
    // Create bottom border for top panel
    wxPanel* bottomBorder = new wxPanel(mainPanel, wxID_ANY, wxDefaultPosition, wxSize(-1, (tileSize/16)));
    bottomBorder->SetBackgroundColour(wxColour(91, 91, 91)); // Dark gray border
    // Create header labels
    timerTopText_ = new wxStaticText(topBar, wxID_ANY, "Timer:", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    wxStaticText* flagTopText = new wxStaticText(topBar, wxID_ANY, "Flags:", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    timerText_ = new wxStaticText(topBar, wxID_ANY, "00:00:00", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    flagCountText_ = new wxStaticText(topBar, wxID_ANY, wxString::Format("0 / %d", gridMines_), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    // Create one font and apply it to all header labels
    wxFont headerFont = timerTopText_->GetFont();
    headerFont.SetPointSize(14);
    headerFont.SetWeight(wxFONTWEIGHT_BOLD);
    timerTopText_->SetFont(headerFont);
    flagTopText->SetFont(headerFont);
    flagCountText_->SetFont(headerFont);
    timerText_->SetFont(headerFont);
    // Vertical sizer for timer labels
    wxBoxSizer* timerColumn = new wxBoxSizer(wxVERTICAL);
    timerColumn->Add(timerTopText_, 0, wxALIGN_CENTER | wxTOP, 2);
    timerColumn->Add(timerText_, 0, wxALIGN_CENTER | wxTOP, 2);
    // Vertical sizer for flag labels
    wxBoxSizer* flagColumn = new wxBoxSizer(wxVERTICAL);
    flagColumn->Add(flagTopText, 0, wxALIGN_CENTER | wxTOP, 2);
    flagColumn->Add(flagCountText_, 0, wxALIGN_CENTER | wxTOP, 2);
    // Horizontal sizer to hold timer and flag columns centered with spacing
    wxBoxSizer* topBarSizer = new wxBoxSizer(wxHORIZONTAL);
    topBarSizer->AddStretchSpacer();
    topBarSizer->Add(timerColumn, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 40);
    topBarSizer->Add(flagColumn, 0, wxALIGN_CENTER_VERTICAL);
    topBarSizer->AddStretchSpacer();
    // Wrap topBarSizer with padding
    wxBoxSizer* topBarPaddingSizer = new wxBoxSizer(wxHORIZONTAL);
    topBarPaddingSizer->Add(topBarSizer, 1, wxEXPAND | wxLEFT | wxRIGHT, 20); // Add horizontal padding
    topBar->SetSizer(topBarPaddingSizer);
    // Load the initial tile image
    wxString filePath = wxString::Format("./img/%dx/e_tile.png", tileSize);
    if (!tileBitmap_.LoadFile(filePath, wxBITMAP_TYPE_PNG)) {
        wxMessageBox("Failed to load " + filePath, "Error", wxOK | wxICON_ERROR);
        Close();
        return;
    }
    // Scaling the tiles
    wxImage img = tileBitmap_.ConvertToImage().Scale(tileSize, tileSize, wxIMAGE_QUALITY_HIGH);
    wxBitmap scaledBitmap(img);
    // Resizing the grid
    wxGridSizer* gridSizer = new wxGridSizer(rows, cols, 0, 0);
    tiles.resize(rows);
    vbox->Add(topBar, 0, wxEXPAND);
    vbox->Add(bottomBorder, 0, wxEXPAND);
    // Binding the game timer
    timer_ = new wxTimer(this);
    Bind(wxEVT_TIMER, &MyFrame::OnTimerUpdate, this);
    // Create and initialize each tile in the grid
    for(int i = 0; i < gridRows_; ++i){
        tiles[i].resize(gridCols_);
        for(int j = 0; j < gridCols_; ++j){
            wxWindowID id = wxWindow::NewControlId();
            wxStaticBitmap* tile = new wxStaticBitmap(mainPanel, id, scaledBitmap, wxDefaultPosition, wxSize(tileSize, tileSize));
            tiles[i][j] = tile;
            idToGridCoord[id] = std::make_pair(i, j);
            // Checking for mouse presses
            tile->Bind(wxEVT_LEFT_UP, &MyFrame::OnLeftClick, this);
            tile->Bind(wxEVT_RIGHT_UP, &MyFrame::OnRightClick, this);
            gridSizer->Add(tile, 1, wxEXPAND);
        }
    }
    vbox->Add(gridSizer, 0, wxALIGN_CENTER);
    mainPanel->SetSizerAndFit(vbox);
    this->Fit();
}

// Updating the visible field between inputs
void MyFrame::DrawVisibleField(const field& plot) {
    for(int row = 0; row < plot.rows; ++row){
        for(int col = 0; col < plot.cols; ++col){
            int val = plot.vissquare[row][col];
            // Reloading the images
            wxBitmap bmp;
            bool loaded = false;
            // Loading the image files for the grid
            if (val == 9) {
                wxString path = wxString::Format("./img/%dx/e_tile.png", tileSize); // Hidden tile
                loaded = bmp.LoadFile(path, wxBITMAP_TYPE_PNG);
            }
            else if (val == 0) {
                wxString path = wxString::Format("./img/%dx/c_tile.png", tileSize); // Clear tile
                loaded = bmp.LoadFile(path, wxBITMAP_TYPE_PNG);
            }
            else if (val == -1) {
                wxString path = wxString::Format("./img/%dx/b_tile.png", tileSize); // Mine tile
                loaded = bmp.LoadFile(path, wxBITMAP_TYPE_PNG);
            }
            else if (val == -2) {
                wxString path = wxString::Format("./img/%dx/x_tile.png", tileSize); // Exploded tile
                loaded = bmp.LoadFile(path, wxBITMAP_TYPE_PNG);
            }
            else if (val >= 1 && val <= 8) {
                wxString path = wxString::Format("./img/%dx/%d_tile.png", tileSize, val); // Number tile
                loaded = bmp.LoadFile(path, wxBITMAP_TYPE_PNG);
            }
            else if (val >= 10) {
                wxString path = wxString::Format("./img/%dx/f_tile.png", tileSize); // Flag tile
                loaded = bmp.LoadFile(path, wxBITMAP_TYPE_PNG);
            }
            else {
                wxString path = wxString::Format("./img/%dx/e_tile.png", tileSize); // Error tile
                loaded = bmp.LoadFile(path, wxBITMAP_TYPE_PNG);
            }
            // Error handling
            if (!loaded || !bmp.IsOk()) {
                wxLogError("Failed to load bitmap for cell [%d, %d] (val: %d)", row, col, val);
                continue;
            }
            wxImage img = bmp.ConvertToImage();
            if (!img.IsOk()) {
                wxLogError("Failed to convert bitmap to image for cell [%d, %d]", row, col);
                continue;
            }
            // Scaling the images
            wxBitmap scaledBitmap(img.Scale(tileSize, tileSize, wxIMAGE_QUALITY_HIGH));
            tiles[row][col]->SetBitmap(scaledBitmap);
        }
    }
    Refresh();  // Refreshing the window
}

// Left click user input
void MyFrame::OnLeftClick(wxMouseEvent& event) {
    if(g_gameOver) return; // Checking if game over
    // Get the tile that was clicked
    wxWindow* tile = dynamic_cast<wxWindow*>(event.GetEventObject());
    if(!tile) return;
    // Get the unique ID of the clicked tile and map it to grid coordinates
    wxWindowID id = tile->GetId();
    if(idToGridCoord.count(id) == 0) return;
    auto [row, col] = idToGridCoord[id];
    setLeftClickCoord(row, col);
    // Starting the game
    if (!g_gameStarted) {
        *g_field = init_game(gridRows_, gridCols_, gridMines_);
        g_gameStarted = true;
        elapsedSeconds_ = 0;
        timerText_->SetLabel("00:00:00");
        timer_->Start(1000); // Update every 1 second
    }
    // Revealing the tiles
    bool hitMine = reveal_tiles(*g_field, {row, col}, false);
    UpdateFlagCount();
    DrawVisibleField(*g_field);
    // Player lose condition: a mine has been hit
    if (hitMine) {
        g_gameOver = true;
        timer_->Stop();
        reveal_mines(*g_field);
        DrawVisibleField(*g_field);
        wxMessageDialog dlg(this, "Oops! You hit a mine. Game over.", "Game Over", wxOK | wxICON_INFORMATION);
        dlg.ShowModal();
    }
    // Player win condition: remaining unopened equals number of mines
    else if ((*g_field).remaining == (*g_field).mines) {
        g_gameOver = true;
        timer_->Stop();
        wxMessageDialog dlg(this, "Congratulations! You won the game!", "Victory", wxOK | wxICON_INFORMATION);
        dlg.ShowModal();
    }
}

// Right click user input
void MyFrame::OnRightClick(wxMouseEvent& event) {
    if (!g_gameStarted) return;
    // Get the tile that was clicked
    wxWindow* tile = dynamic_cast<wxWindow*>(event.GetEventObject());
    if(!tile) return;
    // Get the unique ID of the clicked tile and map it to grid coordinates
    wxWindowID id = tile->GetId();
    if(idToGridCoord.count(id) == 0) return;
    auto [row, col] = idToGridCoord[id];
    // Setting flag and updating field
    if((*g_field).realsquare[row][col] == (*g_field).vissquare[row][col]) return;
    set_flag(*g_field, {row, col});
    UpdateFlagCount();
    DrawVisibleField(*g_field);
}

// Updating tile image
void MyFrame::UpdateTileImage(int row, int col) {
    // Convert the new image (c_tile) into the scaled bitmap
    wxImage img = cTileBitmap_.ConvertToImage().Scale(tileSize, tileSize, wxIMAGE_QUALITY_HIGH);
    wxBitmap scaledBitmap(img);
    // Set the updated image for the clicked tile
    tiles[row][col]->SetBitmap(scaledBitmap);
    Refresh();  // Refreshing the window to update the display
}

// Timer for elapsed gametime
void MyFrame::OnTimerUpdate(wxTimerEvent&) {
    elapsedSeconds_++;
    int hours = elapsedSeconds_ / 3600;
    int minutes = (elapsedSeconds_ % 3600) / 60;
    int seconds = elapsedSeconds_ % 60;
    timerText_->SetLabel(wxString::Format("%02d:%02d:%02d", hours, minutes, seconds));
}

// Counter for flags and mines
void MyFrame::UpdateFlagCount() {
    int flagsPlaced = g_field->flags;
    flagCountText_->SetLabel(wxString::Format("%d / %d", flagsPlaced, gridMines_));
}
