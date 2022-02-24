# Helmz Coil Manipulator

# Build Instructions
1. Clone and install [CppLinuxSerial](https://github.com/gbmhunter/CppLinuxSerial) following the instructions given there.
2. Install the [Pylon SDK](https://www.baslerweb.com/en/sales-support/downloads/software-downloads/) with mpg4 addon.
3. In ~/coil_manipulator
```
mkdir build && cd build
cmake ..
sudo make install
```
4. You are ready to go!


# Features
* Completely C/C++ Based
* Qt5 Frontend
* Basler Pylon + OpenCV integration (prototype)

# Current Progress
* Integrated CppLinuxSerial Library (see credits)
* Formatted message can be sent
* Reception Verified
* Comprehensive backend to be developed
* Most of the documentation transcribed on Notion
* Visual manipulation of tentacle in progress
* File (csv) and Manual input prototype written

* Screenshots
![GUI_Alpha3](images/frontend_alpha3.png)
![Serial_Comm](images/FirstSerialSuccess.png)
# Credits
* [Geoffry Hunter](https://github.com/gbmhunter/CppLinuxSerial) for the Serial Comm C++ Class
