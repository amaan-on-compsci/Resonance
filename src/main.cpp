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
    void FileOpened(wxCommandEvent &event);
    void Painting(wxPaintEvent &event);

    wxPanel *panel;
    wxButton *openButton;
    wxStaticText *infoLabel;

    AudioData audioData; // store audio data as a vector of double vectors
    bool fileOpened;
};

MainFrame::MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(NULL, wxID_ANY, title, pos, size), fileOpened(false)
{
    // customizable panel for the main frame
    panel = new wxPanel(this, wxID_ANY);
    panel->Bind(wxEVT_PAINT, &MainFrame::Painting, this);

    // use this button to choose a file 
    openButton = new wxButton(panel, wxID_ANY, "Choose File     ", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE);
    openButton->Bind(wxEVT_BUTTON, &MainFrame::FileOpened, this);

    // button customization
    wxFont buttonFont(12, wxROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    openButton->SetFont(buttonFont);
    openButton->SetForegroundColour(*wxWHITE);
    openButton->SetBackgroundColour(*wxBLACK);

    // sizers to align the elements within the panel
    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->AddStretchSpacer();
    mainSizer->Add(openButton, 0, wxALIGN_CENTER);
    mainSizer->AddStretchSpacer();

    // set the position for the panel
    panel->SetSizer(mainSizer);
}

void MainFrame::FileOpened(wxCommandEvent &event)
{
    // open a file dialog to let the user choose a .wav file
    wxFileDialog openFileDialog(this, "Open .wav File", "", "", "WAV files (*.wav)|*.wav", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;

    wxString selectedFile = openFileDialog.GetPath();

    // initialize variable to store and load audio data
    AudioFile<double> audioFile;
    if (audioFile.load(selectedFile.ToStdString()))
    {
        // extract audio for both channels
        audioData.samples.clear(); // clear old data
        for (int channel = 0; channel < audioFile.getNumChannels(); ++channel)
        {
            audioData.samples.push_back(audioFile.samples[channel]);
        }
        audioData.sampleRate = audioFile.getSampleRate();

        // to track the status of opened file, update fileOpened
        fileOpened = true;

        // get rid of the choose file button
        openButton->Destroy();

        // =create another button to be used for the next file from the user
        openButton = new wxButton(panel, wxID_ANY, "   Choose File    ", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE);
        openButton->Bind(wxEVT_BUTTON, &MainFrame::FileOpened, this);
        openButton->SetFont(wxFont(12, wxROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
        openButton->SetForegroundColour(*wxWHITE);
        openButton->SetBackgroundColour(*wxBLACK);

        // align the new button
        wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
        mainSizer->AddStretchSpacer();
        mainSizer->Add(openButton, 0, wxALIGN_CENTER);
        mainSizer->AddStretchSpacer();

        // align panel
        panel->SetSizer(mainSizer);

        // draw waveform by repainting panel
        panel->Refresh();
    }
    else
    {
        wxMessageBox("Error loading the selected .wav file.", "Error", wxOK | wxICON_ERROR, this);
    }
}

void MainFrame::Painting(wxPaintEvent &event)
{
    // paint event handler to draw waveform
    wxPaintDC dc(panel);
    wxColor bgColor(30, 30, 30); //set panel bg color
    dc.SetBackground(wxBrush(bgColor));
    dc.Clear();

    // when the file is opened, create a rectangle to draw the waveforms in
    if (fileOpened)
    {
        int width, height;
        panel->GetClientSize(&width, &height);

        // positioning for rectangular frame within panel
        int rectX = 50;                // x coordinate for rectangle
        int rectY = 50;                // y coordinate for rectanle
        int rectWidth = width - 100;   // rectangle width
        int rectHeight = height - 300; // rectangle height

        // center of the rectangle
        int centerX = rectX + rectWidth / 2;

        // for vertically placing waveforms
        int centerYTop = rectY - rectHeight / 200;   
        int centerYBottom = rectY + rectHeight / 2; 

        // draw rectangular frame
        wxPen borderPen(*wxWHITE, 2); // pen settings for the drawing
        dc.SetPen(borderPen);
        dc.SetBrush(*wxTRANSPARENT_BRUSH); // make sure the rectangle isn't filled

        dc.DrawRectangle(rectX, rectY, rectWidth, rectHeight);

        // clipping region restricted to the rectangle
        wxRect clipRect(rectX + 1, rectY + 1, rectWidth - 2, rectHeight - 2);
        dc.SetClippingRegion(clipRect);

        // draw both channels
        wxPen waveformPen1(*wxWHITE, 2); // pen settings for channel 1
        wxPen waveformPen2(*wxRED, 2);   // pen settings for channel 2

        if (!audioData.samples.empty() && audioData.samples.size() >= 2)
        {
            int numSamples = audioData.samples[0].size();
            double scale = static_cast<double>(rectWidth) / numSamples;

            for (int i = 0; i < numSamples - 1; ++i)
            {
                int x1 = static_cast<int>(centerX + (i - numSamples / 2) * scale);
                int y1_1 = static_cast<int>(centerYTop + (audioData.samples[0][i] + 1.0) * rectHeight / 4); 
                int x2 = static_cast<int>(centerX + (i + 1 - numSamples / 2) * scale);
                int y2_1 = static_cast<int>(centerYTop + (audioData.samples[0][i + 1] + 1.0) * rectHeight / 4); 

                int y1_2 = static_cast<int>(centerYBottom + (audioData.samples[1][i] + 1.0) * rectHeight / 4);     
                int y2_2 = static_cast<int>(centerYBottom + (audioData.samples[1][i + 1] + 1.0) * rectHeight / 4); 

                // draw channel 1 line
                dc.SetPen(waveformPen1);
                dc.DrawLine(x1, y1_1, x2, y2_1);

                // draw channel 2 line
                dc.SetPen(waveformPen2);
                dc.DrawLine(x1, y1_2, x2, y2_2);
            }
        }

        // reset the clipping region, no longer within rectangle
        dc.DestroyClippingRegion();

        // display .wav file information
        wxString infoText = wxString::Format("  Samples: %d\n  Frequency: %d Hz", static_cast<int>(audioData.samples[0].size()), audioData.sampleRate);
        wxFont infoFont(20, wxROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
        dc.SetFont(infoFont);
        dc.SetTextForeground(*wxWHITE);
        dc.DrawText(infoText, rectX, rectY + rectHeight + 10);
    }
}

int main(int argc, char *argv[])
{
    // start wxWidgets
    wxApp::SetInstance(new wxApp);
    wxEntryStart(argc, argv);
    wxTheApp->OnInit();

    // create the frame
    MainFrame *frame = new MainFrame("Display Waveform", wxDefaultPosition, wxSize(1000, 900));
    frame->Show(true);

    // start the main event loop
    wxTheApp->MainLoop();

    return 0;
}