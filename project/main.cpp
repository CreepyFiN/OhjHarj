#include "sweeper.h"
#include <wx/wx.h>
#include <wx/image.h>
#include <wx/numdlg.h>
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
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size, int gridSize);

private:
    void OnTileClick(wxMouseEvent& event);
    void UpdateTileImage(int row, int col);
    void DrawVisibleField(const field& plot);

    std::map<wxWindowID, std::pair<int, int>> idToGridCoord;
    std::vector<std::vector<wxStaticBitmap*>> tiles;
    int gridSize_;
    wxBitmap tileBitmap_;
    wxBitmap cTileBitmap_;
    bool isFlagMode_ = false;  // Lippu-tila
    field* g_field = new field();
    bool g_gameStarted = false;

};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    wxInitAllImageHandlers();

    wxNumberEntryDialog dialog(
        NULL,
        "Enter grid size (e.g., 10 for 10x10):",
        "Grid Size",
        "Grid Setup",
        10, 1, 50,
        wxDefaultPosition
    );

    if (dialog.ShowModal() != wxID_OK)
        return false;

    int gridSize = dialog.GetValue();

    MyFrame* frame = new MyFrame("Image Grid Mouse Clicks", wxDefaultPosition, wxDefaultSize, gridSize);
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize&, int gridSize)
    : wxFrame(NULL, wxID_ANY, title, pos, wxDefaultSize), gridSize_(gridSize)
{
    const int tileSize = 32;

    wxPanel* mainPanel = new wxPanel(this);
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

    // Load the initial tile image
    if (!tileBitmap_.LoadFile("img/e_tile.png", wxBITMAP_TYPE_PNG)) {
        wxMessageBox("Failed to load img/e_tile.png", "Error", wxOK | wxICON_ERROR);
        Close();
        return;
    }

    // Load the c_tile image (for the button press)
    if (!cTileBitmap_.LoadFile("img/c_tile.png", wxBITMAP_TYPE_PNG)) {
        wxMessageBox("Failed to load img/c_tile.png", "Error", wxOK | wxICON_ERROR);
        Close();
        return;
    }

    wxImage img = tileBitmap_.ConvertToImage().Scale(tileSize, tileSize, wxIMAGE_QUALITY_HIGH);
    wxBitmap scaledBitmap(img);

    wxGridSizer* gridSizer = new wxGridSizer(gridSize, gridSize, 0, 0);
    tiles.resize(gridSize);

    for (int i = 0; i < gridSize; ++i)
    {
        tiles[i].resize(gridSize);
        for (int j = 0; j < gridSize; ++j)
        {
            wxWindowID id = wxWindow::NewControlId();
            wxStaticBitmap* tile = new wxStaticBitmap(mainPanel, id, scaledBitmap, wxDefaultPosition, wxSize(tileSize, tileSize));
            tiles[i][j] = tile;
            idToGridCoord[id] = std::make_pair(i, j);

            tile->Bind(wxEVT_LEFT_DOWN, &MyFrame::OnTileClick, this);
            gridSizer->Add(tile, 1, wxEXPAND);
        }
    }

    vbox->Add(gridSizer, 0, wxALIGN_CENTER);
    mainPanel->SetSizerAndFit(vbox);
    this->Fit();
}

void MyFrame::DrawVisibleField(const field& plot) {
    const int tileSize = 32;

    for (int row = 0; row < plot.rows; ++row) {
        for (int col = 0; col < plot.cols; ++col) {
            int val = plot.vissquare[row][col];

            wxBitmap bmp;
            bool loaded = false;

            if (val == 9) {
                loaded = bmp.LoadFile("img/e_tile.png", wxBITMAP_TYPE_PNG);
            }
            else if (val == -1 || val == -2) {
                loaded = bmp.LoadFile("img/b_tile.png", wxBITMAP_TYPE_PNG);
            }
            else if (val >= 0 && val <= 8) {
                wxString path = wxString::Format("img/%d_tile.png", val);
                loaded = bmp.LoadFile(path, wxBITMAP_TYPE_PNG);
            }
            else if (val >= 10) {
                loaded = bmp.LoadFile("img/f_tile.png", wxBITMAP_TYPE_PNG);
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



void MyFrame::OnTileClick(wxMouseEvent& event)
{
    wxWindow* tile = dynamic_cast<wxWindow*>(event.GetEventObject());
    if (!tile) return;

    wxWindowID id = tile->GetId();
    if (idToGridCoord.count(id) == 0) return;

    auto [row, col] = idToGridCoord[id];

    if (event.RightDown()) {
        // Oikea klikkaus -> Aseta tai poista lippu
        set_flag(*g_field, {row, col});
        DrawVisibleField(*g_field);
    } else if (event.LeftDown()) {
        // Vasen klikkaus -> Paljasta ruutu
        setFirstClickCoord(row, col);
        if (!g_gameStarted) {
            *g_field = init_game();  // aloita peli ja luo kenttä
            g_gameStarted = true;
        }

        bool hitMine = reveal_tiles(*g_field, {row, col}, false);
        if (hitMine) {
            end_game(*g_field, false);
        }
        DrawVisibleField(*g_field);
    }
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
