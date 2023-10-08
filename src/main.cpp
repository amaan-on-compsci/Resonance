#include <iostream>
#include <wx/wx.h>
#include <wx/filedlg.h>
#include <vector>

#include "AudioFile.h"

struct AudioData
{
    std::vector<std::vector<double>> samples;
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
        // Extract audio data for both channels
        audioData.samples.clear(); // Clear any existing data
        for (int channel = 0; channel < audioFile.getNumChannels(); ++channel)
        {
            audioData.samples.push_back(audioFile.samples[channel]);
        }
        audioData.sampleRate = audioFile.getSampleRate();

        // Set the fileOpened flag to true
        fileOpened = true;

        // Remove the "Choose File" button from the layout
        openButton->Destroy();

        // Create a new "Choose File" button (recurring)
        openButton = new wxButton(panel, wxID_ANY, "   Choose File    ", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE);
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
    // Custom paint event handler to set the background color and draw the waveforms
    wxPaintDC dc(panel);
    wxColor bgColor(30, 30, 30); // Dark gray background color
    dc.SetBackground(wxBrush(bgColor));
    dc.Clear();

    // If a file is opened, draw the waveforms within a bordered rectangle
    if (fileOpened)
    {
        int width, height;
        panel->GetClientSize(&width, &height);

        // Define the position and size of the bordered rectangle
        int rectX = 50;                // X-coordinate of the rectangle
        int rectY = 50;                // Y-coordinate of the rectangle
        int rectWidth = width - 100;   // Width of the rectangle
        int rectHeight = height - 300; // Height of the rectangle

        // Calculate the center of the rectangle
        int centerX = rectX + rectWidth / 2;

        // Calculate the vertical position for waveforms
        int centerYTop = rectY - rectHeight / 200;  // Position for the top channel
        int centerYBottom = rectY + rectHeight / 2; // Position for the bottom channel

        // Draw the bordered rectangle
        wxPen borderPen(*wxWHITE, 2); // White pen with 2-pixel width for the border
        dc.SetPen(borderPen);
        dc.SetBrush(*wxTRANSPARENT_BRUSH); // No fill, only the border

        dc.DrawRectangle(rectX, rectY, rectWidth, rectHeight);

        // Set the clipping region to the inside of the bordered rectangle
        wxRect clipRect(rectX + 1, rectY + 1, rectWidth - 2, rectHeight - 2);
        dc.SetClippingRegion(clipRect);

        // Draw both waveforms within the rectangle with separation
        wxPen waveformPen1(*wxWHITE, 2); // White pen with 2-pixel width for the waveform of channel 1
        wxPen waveformPen2(*wxRED, 2);   // Red pen for the waveform of channel 2

        if (!audioData.samples.empty() && audioData.samples.size() >= 2)
        {
            int numSamples = audioData.samples[0].size();
            double scale = static_cast<double>(rectWidth) / numSamples;

            for (int i = 0; i < numSamples - 1; ++i)
            {
                int x1 = static_cast<int>(centerX + (i - numSamples / 2) * scale);
                int y1_1 = static_cast<int>(centerYTop + (audioData.samples[0][i] + 1.0) * rectHeight / 4); // Adjusted height for top channel
                int x2 = static_cast<int>(centerX + (i + 1 - numSamples / 2) * scale);
                int y2_1 = static_cast<int>(centerYTop + (audioData.samples[0][i + 1] + 1.0) * rectHeight / 4); // Adjusted height for top channel

                int y1_2 = static_cast<int>(centerYBottom + (audioData.samples[1][i] + 1.0) * rectHeight / 4);     // Adjusted height for bottom channel
                int y2_2 = static_cast<int>(centerYBottom + (audioData.samples[1][i + 1] + 1.0) * rectHeight / 4); // Adjusted height for bottom channel

                // Draw top channel waveform
                dc.SetPen(waveformPen1);
                dc.DrawLine(x1, y1_1, x2, y2_1);

                // Draw bottom channel waveform
                dc.SetPen(waveformPen2);
                dc.DrawLine(x1, y1_2, x2, y2_2);
            }
        }

        // Reset the clipping region
        dc.DestroyClippingRegion();

        // Display text with total number of samples and sampling frequency
        wxString infoText = wxString::Format("  Samples: %d\n  Frequency: %d Hz", static_cast<int>(audioData.samples[0].size()), audioData.sampleRate);
        wxFont infoFont(20, wxROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
        dc.SetFont(infoFont);
        dc.SetTextForeground(*wxWHITE);
        dc.DrawText(infoText, rectX, rectY + rectHeight + 10);
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