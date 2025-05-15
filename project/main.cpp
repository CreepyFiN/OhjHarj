#include "sweeper.h"
#include <wx/wx.h>
#include <wx/image.h>
#include <wx/numdlg.h>
#include <wx/spinctrl.h>
#include <wx/msgdlg.h>
#include <vector>
#include <map>

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, int rows, int cols, int mines);

private:
    void OnLeftClick(wxMouseEvent& event);
    void OnRightClick(wxMouseEvent& event);
    void UpdateTileImage(int row, int col);
    void DrawVisibleField(const field& plot);

    std::map<wxWindowID, std::pair<int, int>> idToGridCoord;
    std::vector<std::vector<wxStaticBitmap*>> tiles;
    int gridRows_;
    int gridCols_;
    int gridMines_;
    wxBitmap tileBitmap_;
    wxBitmap cTileBitmap_;
    field* g_field = new field();
    bool g_gameStarted = false;
    bool g_gameOver = false;

};

// User input for grid size and mine count
class GridSetupDialog : public wxDialog
{
public:
    GridSetupDialog(wxWindow* parent)
        : wxDialog(parent, wxID_ANY, "Grid Setup", wxDefaultPosition, wxDefaultSize)
    {
        wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

        wxFlexGridSizer* gridSizer = new wxFlexGridSizer(2, 5, 5);
        gridSizer->Add(new wxStaticText(this, wxID_ANY, "Rows:"), 0, wxALIGN_CENTER_VERTICAL);
        rowsSpin_ = new wxSpinCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize,
                                   wxSP_ARROW_KEYS, 1, 30, 10);
        gridSizer->Add(rowsSpin_);

        gridSizer->Add(new wxStaticText(this, wxID_ANY, "Columns:"), 0, wxALIGN_CENTER_VERTICAL);
        colsSpin_ = new wxSpinCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize,
                                   wxSP_ARROW_KEYS, 1, 50, 10);
        gridSizer->Add(colsSpin_);

        gridSizer->Add(new wxStaticText(this, wxID_ANY, "Mines:"), 0, wxALIGN_CENTER_VERTICAL);
        minesSpin_ = new wxSpinCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize,
                                    wxSP_ARROW_KEYS, 1, 800, 10);
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

        // Initial adjustment
        AdjustMineLimit();
    }

    int GetRows() const { return rowsSpin_->GetValue(); }
    int GetCols() const { return colsSpin_->GetValue(); }
    int GetMines() const { return minesSpin_->GetValue(); }

private:
    wxSpinCtrl* rowsSpin_;
    wxSpinCtrl* colsSpin_;
    wxSpinCtrl* minesSpin_;

    // Adjusting mines so there cannot be more than 80% mines
    void OnGridSizeChanged(wxCommandEvent&){
        AdjustMineLimit();
    }

    void AdjustMineLimit(){
        int rows = rowsSpin_->GetValue();
        int cols = colsSpin_->GetValue();
        int maxMines = std::max(1, (rows * cols * 80) / 100);  // 80% of total grid, minimum 1

        int currentMines = minesSpin_->GetValue();
        minesSpin_->SetRange(1, maxMines);
        if (currentMines > maxMines)
            minesSpin_->SetValue(maxMines);
    }
};


wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit(){
    wxInitAllImageHandlers();

    GridSetupDialog dlg(NULL);
    if (dlg.ShowModal() != wxID_OK)
        return false;

    int rows = dlg.GetRows();
    int cols = dlg.GetCols();
    int mines = dlg.GetMines();

    MyFrame* frame = new MyFrame("Image Grid Mouse Clicks", wxDefaultPosition, rows, cols, mines);
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, int rows, int cols, int mines)    
    : wxFrame(NULL, wxID_ANY, title, pos), gridRows_(rows), gridCols_(cols), gridMines_(mines){
    
    const int tileSize = 32;

    wxPanel* mainPanel = new wxPanel(this);
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

    // Load the initial tile image
    if (!tileBitmap_.LoadFile("img/e_tile.png", wxBITMAP_TYPE_PNG)) {
        wxMessageBox("Failed to load img/e_tile.png", "Error", wxOK | wxICON_ERROR);
        Close();
        return;
    }

    wxImage img = tileBitmap_.ConvertToImage().Scale(tileSize, tileSize, wxIMAGE_QUALITY_HIGH);
    wxBitmap scaledBitmap(img);

    wxGridSizer* gridSizer = new wxGridSizer(rows, cols, 0, 0);
    tiles.resize(rows);

    for (int i = 0; i < gridRows_; ++i){
        tiles[i].resize(gridCols_);
        for (int j = 0; j < gridCols_; ++j){
            wxWindowID id = wxWindow::NewControlId();
            wxStaticBitmap* tile = new wxStaticBitmap(mainPanel, id, scaledBitmap, wxDefaultPosition, wxSize(tileSize, tileSize));
            tiles[i][j] = tile;
            idToGridCoord[id] = std::make_pair(i, j);

            tile->Bind(wxEVT_LEFT_UP, &MyFrame::OnLeftClick, this);
            tile->Bind(wxEVT_RIGHT_UP, &MyFrame::OnRightClick, this);

            gridSizer->Add(tile, 1, wxEXPAND);
        }
    }

    vbox->Add(gridSizer, 0, wxALIGN_CENTER);
    mainPanel->SetSizerAndFit(vbox);
    this->Fit();
}

void MyFrame::DrawVisibleField(const field& plot) {
    const int tileSize = 32;

    for (int row = 0; row < plot.rows; ++row){
        for (int col = 0; col < plot.cols; ++col){
            int val = plot.vissquare[row][col];

            wxBitmap bmp;
            bool loaded = false;

            if (val == 9) {
                loaded = bmp.LoadFile("img/e_tile.png", wxBITMAP_TYPE_PNG);
            }
            else if (val == 0) {
                loaded = bmp.LoadFile("img/c_tile.png", wxBITMAP_TYPE_PNG);
            }
            else if (val == -1 || val == -2) {
                loaded = bmp.LoadFile("img/b_tile.png", wxBITMAP_TYPE_PNG);
            }
            else if (val >= 1 && val <= 8) {
                wxString path = wxString::Format("img/%d_tile.png", val);
                loaded = bmp.LoadFile(path, wxBITMAP_TYPE_PNG);
            }
            else if (val >= 10) {
                loaded = bmp.LoadFile("img/f_tile.png", wxBITMAP_TYPE_PNG);
            }
            else {
                loaded = bmp.LoadFile("img/c_tile.png", wxBITMAP_TYPE_PNG);
            }

            if (!loaded || !bmp.IsOk()) {
                wxLogError("Failed to load bitmap for cell [%d, %d] (val: %d)", row, col, val);
                continue;
            }

            wxImage img = bmp.ConvertToImage();
            if (!img.IsOk()) {
                wxLogError("Failed to convert bitmap to image for cell [%d, %d]", row, col);
                continue;
            }

            wxBitmap scaledBitmap(img.Scale(tileSize, tileSize, wxIMAGE_QUALITY_HIGH));
            tiles[row][col]->SetBitmap(scaledBitmap);
        }
    }
    Refresh();  // Päivitä käyttöliittymä
}



void MyFrame::OnLeftClick(wxMouseEvent& event)
{
    if(g_gameOver) return;
    wxWindow* tile = dynamic_cast<wxWindow*>(event.GetEventObject());
    if (!tile) return;

    wxWindowID id = tile->GetId();
    if (idToGridCoord.count(id) == 0) return;

    auto [row, col] = idToGridCoord[id];

    setFirstClickCoord(row, col);
    if (!g_gameStarted) {
        *g_field = init_game(gridRows_, gridCols_, gridMines_);
        g_gameStarted = true;
    }

    bool hitMine = reveal_tiles(*g_field, {row, col}, false);
    DrawVisibleField(*g_field);
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

void MyFrame::OnRightClick(wxMouseEvent& event)
{
    wxWindow* tile = dynamic_cast<wxWindow*>(event.GetEventObject());
    if (!tile) return;

    wxWindowID id = tile->GetId();
    if (idToGridCoord.count(id) == 0) return;

    auto [row, col] = idToGridCoord[id];

    set_flag(*g_field, {row, col});
    DrawVisibleField(*g_field);
}



void MyFrame::UpdateTileImage(int row, int col)
{
    const int tileSize = 32;

    // Convert the new image (c_tile) into the scaled bitmap
    wxImage img = cTileBitmap_.ConvertToImage().Scale(tileSize, tileSize, wxIMAGE_QUALITY_HIGH);
    wxBitmap scaledBitmap(img);

    // Set the updated image for the clicked tile
    tiles[row][col]->SetBitmap(scaledBitmap);

    Refresh();  // Refresh the window to update the display
}