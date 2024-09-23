# Resonance - Visualize Audio Waveforms from WAV Files

Resonance is a GUI-based application designed to read and visualize .wav audio files by plotting the waveform of each audio channel. This tool provides a clear graphical representation of the waveforms, making it easier to analyze the amplitude and structure of the audio file across multiple channels.

Developed using C++ and the wxWidgets library, the application offers an intuitive interface for loading .wav files and automatically rendering the waveforms for each channel in a clean, visually appealing way.


Key Features:
Load and Render .WAV Files: Easily load .wav files through a simple file dialog and visualize their waveforms on the screen.

Multi-Channel Support: Handles multi-channel audio files, drawing separate waveforms for each channel.

Dynamic Display: Automatically centers and scales the waveform display based on the audio file and screen dimensions.

Real-Time Information: Displays sample count and frequency (sampling rate in Hz) of the loaded audio file.

Customizable GUI: Uses wxWidgets for a highly customizable and responsive graphical user interface.


Technologies Used:
C++: Core programming language for implementing audio data handling and GUI interaction.

wxWidgets: Cross-platform GUI toolkit for creating the application's user interface and handling file dialogs, button interactions, and drawing.

AudioFile: An external library for loading and processing .wav audio files.

# How to Build/Run (How I last did it):

Clone this repository, install wxWidgets (initialize submodules if needed), create a build directory and configure the project with CMake:

mkdir build
cd build
cmake ..
cmake --build . --config Debug

Run with ./exe_name
