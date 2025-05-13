#include <wx/wx.h>
#include <wx/statbmp.h> // For wxStaticBitmap
#include <wx/image.h>   // For image handling

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);

private:
    void OnButtonClick(wxCommandEvent& event);
    wxButton* gridButtons[10][10];
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    wxInitAllImageHandlers(); // Initialize image handlers (for PNG support)
    MyFrame *frame = new MyFrame("10x10 Button Grid with Image", wxDefaultPosition, wxDefaultSize);
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &)
    : wxFrame(NULL, wxID_ANY, title, pos, wxDefaultSize)
{
    int buttonSize = 60;
    int margin = 10;

    // Outer panel and sizer
    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

    // Grid panel for buttons
    wxPanel* gridPanel = new wxPanel(panel);
    gridPanel->SetSize(wxSize(buttonSize * 10 + margin * 2, buttonSize * 10 + margin * 2));

    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            int buttonID = i * 10 + j;
            gridButtons[i][j] = new wxButton(gridPanel, buttonID, "",
                wxPoint(j * buttonSize + margin, i * buttonSize + margin),
                wxSize(buttonSize, buttonSize));

            gridButtons[i][j]->Bind(wxEVT_BUTTON, &MyFrame::OnButtonClick, this);
        }
    }

    // Add grid panel to vertical sizer
    vbox->Add(gridPanel, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);

    // Load image and add below
    wxImage image("img/c_tile.png", wxBITMAP_TYPE_PNG);
    if (image.IsOk())
    {
        wxStaticBitmap* imageCtrl = new wxStaticBitmap(panel, wxID_ANY, wxBitmap(image));
        vbox->Add(imageCtrl, 0, wxALIGN_CENTER | wxBOTTOM, 10);
    }
    else
    {
        wxStaticText* errorText = new wxStaticText(panel, wxID_ANY, "Failed to load c_tile.png");
        vbox->Add(errorText, 0, wxALIGN_CENTER | wxBOTTOM, 10);
    }

    panel->SetSizerAndFit(vbox);
    this->Fit(); // Adjust frame to fit content
}

void MyFrame::OnButtonClick(wxCommandEvent& event)
{
    int buttonID = event.GetId();
    int row = buttonID / 10;
    int col = buttonID % 10;
    gridButtons[row][col]->SetLabel(wxString::Format("%d", buttonID));
}
