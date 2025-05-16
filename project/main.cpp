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
    const int tileSizeImg = 16; // Pixel size of images (Väliaikainen, yhdistä tileSize kanssa) 
    
    /*!!! LISÄÄ 32x JA 64x VERSIOT KUVISTA, JOTTA KUVAT OVAT TERÄVÄMPIÄ (i.e. /img/64x/e_tile.png) !!!*/
};

// User input for grid size and mine count
class GridSetupDialog : public wxDialog {
public:
    GridSetupDialog(wxWindow* parent)
        : wxDialog(parent, wxID_ANY, "Game initiation", wxDefaultPosition, wxDefaultSize) {

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

        mainSizer->Add(gridSizer, 1, wxALL | wxEXPAND, 10);

        wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
        btnSizer->AddStretchSpacer();
        btnSizer->Add(new wxButton(this, wxID_OK), 0, wxALL, 5);
        btnSizer->Add(new wxButton(this, wxID_CANCEL), 0, wxALL, 5);

        mainSizer->Add(btnSizer, 0, wxEXPAND | wxRIGHT | wxBOTTOM, 5);

        SetSizerAndFit(mainSizer);

        // Bind change events to update mine limit dynamically
        rowsSpin_->Bind(wxEVT_SPINCTRL, &GridSetupDialog::OnGridSizeChanged, this);
        colsSpin_->Bind(wxEVT_SPINCTRL, &GridSetupDialog::OnGridSizeChanged, this);

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
        if (currentMines > maxMines) {
            minesSpin_->SetValue(maxMines);
        }
        // Update the label text
        mineLabel_->SetLabel(wxString::Format("Mines (MAX %d):", maxMines));
        Layout(); // Ensure UI updates properly
    }
};

wxIMPLEMENT_APP(MyApp);

// Game initiation
bool MyApp::OnInit() {
    wxInitAllImageHandlers();

    GridSetupDialog dlg(NULL);
    if(dlg.ShowModal() != wxID_OK) return false;

    int rows = dlg.GetRows();
    int cols = dlg.GetCols();
    int mines = dlg.GetMines();

    MyFrame* frame = new MyFrame("Minesweeper", wxDefaultPosition, rows, cols, mines);
    frame->Show(true);
    return true;
}

// Main
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, int rows, int cols, int mines)    
    : wxFrame(NULL, wxID_ANY, title, pos), gridRows_(rows), gridCols_(cols), gridMines_(mines) {
    // Changing size of tiles according to grid size
    if (rows > 30 || cols > 50) tileSize = 16;
    else if (rows <= 12 && cols <= 20) tileSize = 64;

    wxPanel* mainPanel = new wxPanel(this);
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
    // Load the initial tile image
    wxString filePath = wxString::Format("img/%dx/e_tile.png", tileSizeImg);
    if (!tileBitmap_.LoadFile(filePath, wxBITMAP_TYPE_PNG)) {
        wxMessageBox("Failed to load e_tile.png", "Error", wxOK | wxICON_ERROR);
        Close();
        return;
    }
    // Scaling the tiles
    wxImage img = tileBitmap_.ConvertToImage().Scale(tileSize, tileSize, wxIMAGE_QUALITY_HIGH);
    wxBitmap scaledBitmap(img);
    // Resizing the grid
    wxGridSizer* gridSizer = new wxGridSizer(rows, cols, 0, 0);
    tiles.resize(rows);

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
                wxString path = wxString::Format("img/%dx/e_tile.png", tileSizeImg); // Hidden tile
                loaded = bmp.LoadFile(path, wxBITMAP_TYPE_PNG);
            }
            else if (val == 0) {
                wxString path = wxString::Format("img/%dx/c_tile.png", tileSizeImg); // Clear tile
                loaded = bmp.LoadFile(path, wxBITMAP_TYPE_PNG);
            }
            else if (val == -1 || val == -2) {
                wxString path = wxString::Format("img/%dx/b_tile.png", tileSizeImg); // Mine tile
                loaded = bmp.LoadFile(path, wxBITMAP_TYPE_PNG);
            }
            else if (val >= 1 && val <= 8) {
                wxString path = wxString::Format("img/%dx/%d_tile.png", tileSizeImg, val); // Number tile
                loaded = bmp.LoadFile(path, wxBITMAP_TYPE_PNG);
            }
            else if (val >= 10) {
                wxString path = wxString::Format("img/%dx/f_tile.png", tileSizeImg); // Flag tile
                loaded = bmp.LoadFile(path, wxBITMAP_TYPE_PNG);
            }
            else {
                wxString path = wxString::Format("img/%dx/c_tile.png", tileSizeImg); // Error tile
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
    wxWindow* tile = dynamic_cast<wxWindow*>(event.GetEventObject());
    if(!tile) return;
    wxWindowID id = tile->GetId();
    if(idToGridCoord.count(id) == 0) return;
    auto [row, col] = idToGridCoord[id];
    setLeftClickCoord(row, col);
    // Starting the game
    if (!g_gameStarted) {
        *g_field = init_game(gridRows_, gridCols_, gridMines_);
        g_gameStarted = true;
    }
    // Revealing the tiles
    bool hitMine = reveal_tiles(*g_field, {row, col}, false);
    DrawVisibleField(*g_field);
    // Player lose condition: a mine has been hit
    if (hitMine) {
        g_gameOver = true;
        reveal_mines(*g_field);
        DrawVisibleField(*g_field);
        wxMessageDialog dlg(this, "Oops! You hit a mine. Game over.", "Game Over", wxOK | wxICON_INFORMATION);
        dlg.ShowModal();
    }
    // Player win condition: remaining unopened equals number of mines
    else if ((*g_field).remaining == (*g_field).mines) {
        g_gameOver = true;
        wxMessageDialog dlg(this, "Congratulations! You won the game!", "Victory", wxOK | wxICON_INFORMATION);
        dlg.ShowModal();
    }
}

// Right click user input
void MyFrame::OnRightClick(wxMouseEvent& event) {
    if (!g_gameStarted) return;
    wxWindow* tile = dynamic_cast<wxWindow*>(event.GetEventObject());
    if(!tile) return;
    wxWindowID id = tile->GetId();
    if(idToGridCoord.count(id) == 0) return;
    auto [row, col] = idToGridCoord[id];
    // Setting flag and updating field
    set_flag(*g_field, {row, col});
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