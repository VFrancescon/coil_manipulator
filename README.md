# Helmz Coil Manipulator

# Build Instructions
1. Clone and install [CppLinuxSerial](https://github.com/VFrancescon/CppLinuxSerial) following the instructions given there.*
2. Install the [Pylon SDK](https://www.baslerweb.com/en/sales-support/downloads/software-downloads/) with mpg4 addon.
3. In ~/coil_manipulator


\*PLEASE NOTE:
We use my fork of the library as the original repo currently do not support setting flow control at run time.
I put a merge request out and hopefullythey will soon and we can resume to using their release branch.
```
mkdir build && cd build
cmake ..
sudo make install
```
4. You are ready to go!

***NOTE***

`sudo make install` is only required if the files in the libs/ directory are modified.

        That is because the libraries are installed on the system in /usr/local/include. Which allows you to include the libraries direclty into any application written for the system, only needing to link_libraries in the CMake.

Else, you can just run `make` optionally specifying which executable to compile specifically.
Example: `make initial_test` or `make all`

# Features
* Completely C/C++ Based
* Qt5 Frontend
* Basler Pylon + OpenCV integration (prototype)
* Low level library written for Serial Comm to PSUs
* Low level library written for SCPI Comm to Teslameter (Lakeshore F71)
* Low Level library written for Serial Comm to Linear Actuator

# Currently in Progress
* Middleware Layer that abstracts all low-level libraries.

# Screenshots
![GUI_Alpha3](images/frontend_alpha3.png)
![Serial_Comm](images/FirstSerialSuccess.png)
# Credits
* [Geoffry Hunter](https://github.com/gbmhunter/CppLinuxSerial) for the Serial Comm C++ Class
