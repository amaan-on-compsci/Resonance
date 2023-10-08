// // #include <iostream>
// // #include <SDL3/SDL.h>
// // #include <stdio.h>
// // #include <wx/wx.h>
// // #include <wx/filedlg.h>
// // #include "AudioFile.h"

// // int main(int argc, char *argv[])
// // {
// //     // Initialize SDL
// //     if (SDL_Init(SDL_INIT_VIDEO) < 0)
// //     {
// //         std::cerr << "SDL Initialization Error: " << SDL_GetError() << std::endl;
// //         return 1;
// //     }

// //     // Create a resizable window
// //     SDL_Window *window = SDL_CreateWindow(
// //         "Waveform Visualizer",
// //         1000, 900,
// //         SDL_WINDOW_RESIZABLE);

// //     if (!window)
// //     {
// //         std::cerr << "Window Creation Error: " << SDL_GetError() << std::endl;
// //         return 1;
// //     }

// //     // Create a renderer
// //     SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL, SDL_RENDERER_ACCELERATED);

// //     if (!renderer)
// //     {
// //         std::cerr << "Renderer Creation Error: " << SDL_GetError() << std::endl;
// //         SDL_DestroyWindow(window);
// //         SDL_Quit();
// //         return 1;
// //     }

// //     // Set the initial background color (dark mode)
// //     SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
// //     SDL_RenderClear(renderer);
// //     SDL_RenderPresent(renderer);

// //     bool running = true;
// //     while (running)
// //     {
// //         SDL_Event event;
// //         while (SDL_PollEvent(&event))
// //         {
// //             if (event.type == SDL_EVENT_QUIT)
// //             {
// //                 running = false;
// //             }
// //             else if (event.type >= SDL_EVENT_WINDOW_FIRST && event.type <= SDL_EVENT_WINDOW_LAST)
// //             {
// //                 if (event.window.type == SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED)
// //                 {
// //                     // Handle window resize
// //                     SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
// //                     SDL_RenderClear(renderer);
// //                     SDL_RenderPresent(renderer);
// //                 }
// //             }
// //         }
// //     }

// //     // Cleanup and exit
// //     SDL_DestroyRenderer(renderer);
// //     SDL_DestroyWindow(window);
// //     SDL_Quit();

// //     return 0;
// // }
// #include <iostream>
// #include <SDL3/SDL.h>
// #include <wx/wx.h>
// #include <wx/filedlg.h>
// #include "AudioFile.h"

// // Declare a custom wxWidgets frame class
// class MyFrame : public wxFrame
// {
// public:
//     MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
//     // SDL_Renderer* getFrameRenderer() {return sdlRenderer;}
//     // SDL_Window* getFrameWindow() {return sdlWindow;}
// private:
//     void OnOpenFile(wxCommandEvent& event);
    
//     wxPanel* panel;
//     wxButton* openButton;
//     // SDL_Window* sdlWindow;
//     // SDL_Renderer* sdlRenderer;
// };

// MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
//     : wxFrame(NULL, wxID_ANY, title, pos, size)
// {
//     // Create a panel to host SDL rendering
//     panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE);

//     // Create an "Open File" button
//     openButton = new wxButton(this, wxID_ANY, "Choose File", wxDefaultPosition, wxDefaultSize, wxCENTER);
//     openButton->Bind(wxEVT_BUTTON, &MyFrame::OnOpenFile, this);

//     // // Initialize SDL
//     // if (SDL_Init(SDL_INIT_VIDEO) < 0)
//     // {
//     //     std::cerr << "SDL Initialization Error: " << SDL_GetError() << std::endl;
//     //     return;
//     // }

//     // // Create an SDL window within the panel
//     // sdlWindow = SDL_CreateWindowFrom(panel->GetHWND());
//     // if (!sdlWindow)
//     // {
//     //     std::cerr << "SDL Window Creation Error: " << SDL_GetError() << std::endl;
//     //     return;
//     // }

//     // // Create an SDL renderer
//     // sdlRenderer = SDL_CreateRenderer(sdlWindow, NULL, SDL_RENDERER_ACCELERATED);
//     // if (!sdlRenderer)
//     // {
//     //     std::cerr << "SDL Renderer Creation Error: " << SDL_GetError() << std::endl;
//     //     return;
//     // }

//     // Set the initial background color (dark mode)
// //    SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255);
// //    SDL_RenderClear(sdlRenderer);
// //    SDL_RenderPresent(sdlRenderer);
// }

// void MyFrame::OnOpenFile(wxCommandEvent& event)
// {
//     // Create a file dialog to choose a .wav file
//     wxFileDialog openFileDialog(this, "Open .wav File", "", "", "WAV files (*.wav)|*.wav", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

//     if (openFileDialog.ShowModal() == wxID_CANCEL)
//         return;

//     wxString selectedFile = openFileDialog.GetPath();
//     // Here you can open the selected .wav file using AudioFile or your audio processing logic.

//     // Example:
//     // AudioFile audioFile;
//     // audioFile.load(selectedFile.ToStdString());

//     // Update your SDL rendering or audio processing with the loaded file.

//     // Display the selected file path
//     wxMessageBox("Selected File: " + selectedFile, "File Selected", wxOK | wxICON_INFORMATION, this);
// }

// int main(int argc, char* argv[])
// {
//     // Initialize wxWidgets
//     wxApp::SetInstance(new wxApp);
//     wxEntryStart(argc, argv);
//     wxTheApp->OnInit();

//     // Create the custom frame
//     MyFrame* frame = new MyFrame("Waveform Visualizer", wxDefaultPosition, wxSize(1000, 900));
//     frame->Show(true);

//     // Start the wxWidgets event loop
//     wxTheApp->MainLoop();

//     // Cleanup and exit
// //    SDL_DestroyRenderer(frame->getFrameRenderer());
//     // SDL_DestroyWindow(frame->getFrameWindow());
//     // SDL_Quit();

//     return 0;
// }
// #include <iostream>
// #include <SDL3/SDL.h>
// #include <stdio.h>
// #include <wx/wx.h>
// #include <wx/filedlg.h>
// #include "AudioFile.h"

// int main(int argc, char *argv[])
// {
//     // Initialize SDL
//     if (SDL_Init(SDL_INIT_VIDEO) < 0)
//     {
//         std::cerr << "SDL Initialization Error: " << SDL_GetError() << std::endl;
//         return 1;
//     }

//     // Create a resizable window
//     SDL_Window *window = SDL_CreateWindow(
//         "Waveform Visualizer",
//         1000, 900,
//         SDL_WINDOW_RESIZABLE);

//     if (!window)
//     {
//         std::cerr << "Window Creation Error: " << SDL_GetError() << std::endl;
//         return 1;
//     }

//     // Create a renderer
//     SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL, SDL_RENDERER_ACCELERATED);

//     if (!renderer)
//     {
//         std::cerr << "Renderer Creation Error: " << SDL_GetError() << std::endl;
//         SDL_DestroyWindow(window);
//         SDL_Quit();
//         return 1;
//     }

//     // Set the initial background color (dark mode)
//     SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
//     SDL_RenderClear(renderer);
//     SDL_RenderPresent(renderer);

//     bool running = true;
//     while (running)
//     {
//         SDL_Event event;
//         while (SDL_PollEvent(&event))
//         {
//             if (event.type == SDL_EVENT_QUIT)
//             {
//                 running = false;
//             }
//             else if (event.type >= SDL_EVENT_WINDOW_FIRST && event.type <= SDL_EVENT_WINDOW_LAST)
//             {
//                 if (event.window.type == SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED)
//                 {
//                     // Handle window resize
//                     SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
//                     SDL_RenderClear(renderer);
//                     SDL_RenderPresent(renderer);
//                 }
//             }
//         }
//     }

//     // Cleanup and exit
//     SDL_DestroyRenderer(renderer);
//     SDL_DestroyWindow(window);
//     SDL_Quit();

//     return 0;
// }
///////////////////////////////////////////////////////////////
// #include <iostream>
// #include <SDL3/SDL.h>
// #include <wx/wx.h>
// #include <wx/filedlg.h>
// #include "AudioFile.h"

// // Declare a custom wxWidgets frame class
// class MyFrame : public wxFrame
// {
// public:
//     MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
// private:
//     void OnOpenFile(wxCommandEvent& event);
    
//     wxPanel* panel;
//     wxButton* openButton;
// };

// MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
//     : wxFrame(NULL, wxID_ANY, title, pos, size)
// {
//     // Create a panel to host SDL rendering
//     panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE);

//     // Create an "Open File" button
//     openButton = new wxButton(this, wxID_ANY, "Choose File", wxDefaultPosition, wxDefaultSize, wxCENTER);
//     openButton->Bind(wxEVT_BUTTON, &MyFrame::OnOpenFile, this);
// }

// void MyFrame::OnOpenFile(wxCommandEvent& event)
// {
//     // Create a file dialog to choose a .wav file
//     wxFileDialog openFileDialog(this, "Open .wav File", "", "", "WAV files (*.wav)|*.wav", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

//     if (openFileDialog.ShowModal() == wxID_CANCEL)
//         return;

//     wxString selectedFile = openFileDialog.GetPath();
//     // Here you can open the selected .wav file using AudioFile or your audio processing logic.

//     // Example:
//     // AudioFile audioFile;
//     // audioFile.load(selectedFile.ToStdString());

//     // Update your SDL rendering or audio processing with the loaded file.

//     // Display the selected file path
//     wxMessageBox("Selected File: " + selectedFile, "File Selected", wxOK | wxICON_INFORMATION, this);
// }

// int main(int argc, char* argv[])
// {
//     // Initialize wxWidgets
//     wxApp::SetInstance(new wxApp);
//     wxEntryStart(argc, argv);
//     wxTheApp->OnInit();

//     // Create the custom frame
//     MyFrame* frame = new MyFrame("Waveform Visualizer", wxDefaultPosition, wxSize(1000, 900));
//     frame->Show(true);

//     // Start the wxWidgets event loop
//     wxTheApp->MainLoop();

//     return 0;
// }
/////////////////////////////
#include <iostream>
#include <SDL3/SDL.h>
#include <wx/wx.h>
#include "AudioFile.h"
#include <wx/filedlg.h>

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
private:
    void OnOpenFile(wxCommandEvent& event);
    void OnPaint(wxPaintEvent& event);

    wxPanel* panel;
    wxButton* openButton;
};

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    // Create a custom panel to set the background color
    panel = new wxPanel(this, wxID_ANY);
    panel->Bind(wxEVT_PAINT, &MyFrame::OnPaint, this);

    // Create an "Open File" button and center it horizontally
    openButton = new wxButton(panel, wxID_ANY, "Choose File     ", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE);
    openButton->Bind(wxEVT_BUTTON, &MyFrame::OnOpenFile, this);

    // Set a nicer font and style for the button
    wxFont buttonFont(12, wxROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    openButton->SetFont(buttonFont);
    openButton->SetForegroundColour(*wxWHITE);
    openButton->SetBackgroundColour(*wxBLACK);

    // Create a vertical box sizer to center the button vertically
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->AddStretchSpacer();
    mainSizer->Add(openButton, 0, wxALIGN_CENTER);
    mainSizer->AddStretchSpacer();

    // Set the sizer for the custom panel
    panel->SetSizer(mainSizer);
}

void MyFrame::OnOpenFile(wxCommandEvent& event)
{
    // Create a file dialog to choose a .wav file
    wxFileDialog openFileDialog(this, "Open .wav File", "", "", "WAV files (*.wav)|*.wav", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;

    wxString selectedFile = openFileDialog.GetPath();
    // Here you can open the selected .wav file using AudioFile or your audio processing logic.

    // Example:
    // AudioFile audioFile;
    // audioFile.load(selectedFile.ToStdString());

    // Update your SDL rendering or audio processing with the loaded file.

    // Display the selected file path
    wxMessageBox("Selected File: " + selectedFile, "File Selected", wxOK | wxICON_INFORMATION, this);
}

void MyFrame::OnPaint(wxPaintEvent& event)
{
    // Custom paint event handler to set the background color
    wxPaintDC dc(panel);
    wxColor bgColor(30, 30, 30); // Dark gray background color
    dc.SetBackground(wxBrush(bgColor));
    dc.Clear();
}

int main(int argc, char* argv[])
{
    // Initialize wxWidgets
    wxApp::SetInstance(new wxApp);
    wxEntryStart(argc, argv);
    wxTheApp->OnInit();

    // Create the custom frame
    MyFrame* frame = new MyFrame("Waveform Visualizer", wxDefaultPosition, wxSize(1000, 900));
    frame->Show(true);

    // Start the wxWidgets event loop
    wxTheApp->MainLoop();

    return 0;
}



