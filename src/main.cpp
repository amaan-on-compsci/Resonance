#include <iostream>
#include <SDL.h>
#include <wx/wx.h>
#include <wx/filedlg.h>
#include <vector>

#include "AudioFile.h"

struct AudioData {
    std::vector<double> samples;
    int sampleRate;

    AudioData() : sampleRate(0) {}
};

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size);

private:
    void OnOpenFile(wxCommandEvent &event);
    void OnPaint(wxPaintEvent &event);

    wxPanel *panel;
    wxButton *openButton;
    wxStaticText *infoLabel;

    AudioData audioData;
    bool fileOpened;
};
 
MainFrame::MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(NULL, wxID_ANY, title, pos, size), fileOpened(false)
{
    // Create a custom panel to set the background color
    panel = new wxPanel(this, wxID_ANY);
    panel->Bind(wxEVT_PAINT, &MainFrame::OnPaint, this);

    // Create an "Open File" button and center it horizontally
    openButton = new wxButton(panel, wxID_ANY, "Choose File     ", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE);
    openButton->Bind(wxEVT_BUTTON, &MainFrame::OnOpenFile, this);

    // Set a nicer font and style for the button
    wxFont buttonFont(12, wxROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    openButton->SetFont(buttonFont);
    openButton->SetForegroundColour(*wxWHITE);
    openButton->SetBackgroundColour(*wxBLACK);

    // Create a vertical box sizer to center the button vertically
    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->AddStretchSpacer();
    mainSizer->Add(openButton, 0, wxALIGN_CENTER);
    mainSizer->AddStretchSpacer();

    // Set the sizer for the custom panel
    panel->SetSizer(mainSizer);
}

void MainFrame::OnOpenFile(wxCommandEvent &event)
{
    // Create a file dialog to choose a .wav file
    wxFileDialog openFileDialog(this, "Open .wav File", "", "", "WAV files (*.wav)|*.wav", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;

    wxString selectedFile = openFileDialog.GetPath();

    // Load the selected .wav file using AudioFile
    AudioFile<double> audioFile;
    if (audioFile.load(selectedFile.ToStdString()))
    {
        // Extract audio data
        audioData.samples = audioFile.samples[0];
        audioData.sampleRate = audioFile.getSampleRate();

        // Set the fileOpened flag to true
        fileOpened = true;

        // Remove the "Choose File" button from the layout
        openButton->Destroy();

        // Create a new "Choose File" button (recurring)
        openButton = new wxButton(panel, wxID_ANY, " Choose File     ", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE);
        openButton->Bind(wxEVT_BUTTON, &MainFrame::OnOpenFile, this);
        openButton->SetFont(wxFont(12, wxROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
        openButton->SetForegroundColour(*wxWHITE);
        openButton->SetBackgroundColour(*wxBLACK);

        // Create a vertical box sizer to center the button vertically (recurring)
        wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
        mainSizer->AddStretchSpacer();
        mainSizer->Add(openButton, 0, wxALIGN_CENTER);
        mainSizer->AddStretchSpacer();

        // Set the sizer for the custom panel (recurring)
        panel->SetSizer(mainSizer);

        // Trigger a repaint event to draw the waveform
        panel->Refresh();
    }
    else
    {
        wxMessageBox("Error loading the selected .wav file.", "Error", wxOK | wxICON_ERROR, this);
    }
}

void MainFrame::OnPaint(wxPaintEvent &event)
{
    // Custom paint event handler to set the background color and draw the waveform
    wxPaintDC dc(panel);
    wxColor bgColor(30, 30, 30); // Dark gray background color
    dc.SetBackground(wxBrush(bgColor));
    dc.Clear();

    // If a file is opened, draw the waveform within a bordered rectangle
    if (fileOpened)
    {
        int width, height;
        panel->GetClientSize(&width, &height);

        // Define the position and size of the bordered rectangle
        int rectX = 50;              // X-coordinate of the rectangle
        int rectY = 50;              // Y-coordinate of the rectangle
        int rectWidth = width - 100; // Width of the rectangle
        int rectHeight = height / 2; // Height of the rectangle (top half of the screen)

        // Calculate the center of the rectangle
        int centerX = rectX + rectWidth / 2;

        // Calculate the vertical center for waveform plotting, keeping it higher
        int centerY = rectY + rectHeight / 4;

        // Draw the bordered rectangle
        wxPen borderPen(*wxWHITE, 2); // White pen with 2-pixel width for the border
        dc.SetPen(borderPen);
        dc.SetBrush(*wxTRANSPARENT_BRUSH); // No fill, only the border

        dc.DrawRectangle(rectX, rectY, rectWidth, rectHeight);

        // Set the clipping region to the inside of the bordered rectangle
        wxRect clipRect(rectX + 1, rectY + 1, rectWidth - 2, rectHeight - 2);
        dc.SetClippingRegion(clipRect);

        // Draw the waveform centered within the rectangle
        wxPen waveformPen(*wxWHITE, 2); // White pen with 2-pixel width for the waveform
        dc.SetPen(waveformPen);

        if (!audioData.samples.empty())
        {
            int numSamples = audioData.samples.size();
            double scale = static_cast<double>(rectWidth) / numSamples;

            for (int i = 0; i < numSamples - 1; ++i)
            {
                int x1 = static_cast<int>(centerX + (i - numSamples / 2) * scale);
                int y1 = static_cast<int>(centerY + (audioData.samples[i] + 1.0) * rectHeight / 4); // Adjusted height
                int x2 = static_cast<int>(centerX + (i + 1 - numSamples / 2) * scale);
                int y2 = static_cast<int>(centerY + (audioData.samples[i + 1] + 1.0) * rectHeight / 4); // Adjusted height

                dc.DrawLine(x1, y1, x2, y2);
            }
        }

        // Reset the clipping region
        dc.DestroyClippingRegion();

        // Display text with total number of samples and sampling frequency
        wxString infoText = wxString::Format("  Samples: %d\n  Frequency: %d Hz", static_cast<int>(audioData.samples.size()), audioData.sampleRate);

        // Create a wxStaticText control
        infoLabel = new wxStaticText(panel, wxID_ANY, infoText, wxPoint(rectX, rectY + rectHeight + 10), wxSize(300, 70));
        wxFont infoFont(20, wxROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
        infoLabel->SetFont(infoFont);
        infoLabel->SetBackgroundColour(*wxBLACK);
        infoLabel->SetForegroundColour(*wxWHITE);
        infoLabel->SetSize(infoLabel->GetBestSize()); // Make the text sizeable
    }
}

int main(int argc, char *argv[])
{
    // Initialize wxWidgets
    wxApp::SetInstance(new wxApp);
    wxEntryStart(argc, argv);
    wxTheApp->OnInit();

    // Create the custom frame
    MainFrame *frame = new MainFrame("Display Waveform", wxDefaultPosition, wxSize(1000, 900));
    frame->Show(true);

    // Start the wxWidgets event loop
    wxTheApp->MainLoop();

    return 0;
}
