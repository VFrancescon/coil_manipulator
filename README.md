# Helmz Coil Manipulator

## WARNING

This repo is now archived. A minimal version of the coil back-end has been ported to the [minimal repo](https://github.com/VFrancescon/coil_libs) to cut down on dependencies.

## Dependencies

### Functional

* Install the [Pylon SDK](https://www.baslerweb.com/en/sales-support/downloads/software-downloads/) with mpg4 addon.
* [OpenCV](https://opencv.org/releases/)
* [CppLinuxSerial](hhttps://github.com/gbmhunter/CppLinuxSerial)
* [A-Star](https://github.com/VFrancescon/a-star)*

\*PLEASE NOTE:
Forked from main to introduce some extra functionality. Pull requests are out and the original repos will be restored in the guides when appropriate. 

Both repos are also included as submodules. Therefore, upon cloning, include them using:

`git submodule init`

`git submodule update`

Then follow install instructions for each repo (CppLinuxSerial) only for now.

### Documentation

[Read the documentation here](https://vfrancescon.github.io/coil_manipulator/)

* [Doxygen](https://www.doxygen.nl/download.html#srcbin)

* [graphviz](http://www.graphviz.org/download/)

\*NOTE: Follow [this](https://devblogs.microsoft.com/cppblog/clear-functional-c-documentation-with-sphinx-breathe-doxygen-cmake/) guide for detailed Doxygen instructions. It was decided Sphinx was not worth it, so we only need the Doxygen section.
Also, for compatibility, install from source. The bins and apt packages hate working on ubuntu 18.

## Build Instructions

1. In ~/coil_manipulator

2. Execute

```bash
mkdir build && cd build
cmake ..
sudo make install
```

3. You are ready to go!

### Note

`sudo make install` is only required if the files in the libs/ directory are modified.

```
That is because the libraries are installed on the system in /usr/local/include. 
Which allows you to include the libraries direclty into any application written for the system. 
Only needing to link_libraries in the CMAKE.
```

Else, you can just run `make` optionally specifying which executable to compile.
Example: `make initial_test` or `make all`

The Doxygen documentation can be built with `make Doxygen`. Once built, it can be accessed by opening the index.html file generated with your favourite browser.

E.g. (assuming you are in build/ and have compiled the project fully):

`firefox docs/html/index.html`

## Features

* Completely C/C++ Based
* Qt5 Frontend
* Basler Pylon + OpenCV integration (prototype)
* Low level library written for Serial Comm to PSUs
* Low level library written for SCPI Comm to Teslameter (Lakeshore F71)
* Low Level library written for Serial Comm to Linear Actuator
* Functional (Barebones) middle-ware layer to control the above components

## Currently in Progress

* Image processing and control module

## Screenshots

![GUI_Alpha3](images/frontend_alpha3.png)
![Serial_Comm](images/FirstSerialSuccess.png)

## Credits

* [Geoffry Hunter](https://github.com/gbmhunter/CppLinuxSerial) for the Serial Comm C++ Class
* [Damian Barczyński](https://github.com/daancode/a-star) for the C++ A* implementation
