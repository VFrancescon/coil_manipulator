/*! @mainpage Introduction
 *
 * @tableofcontents
 * 
 * @section intro_sec Overview
 *
 * Set of libraries covering all the Low-Level control of a set of (currently) 3 DXKDP Power Supplies connected to a a Tri-axis Helmholtz Coil.
 *
 * Also covers control of a Lakeshore F71 Tri-axis Tesla Meter and generic Stepper Motor to introduce the sample in the workspace.
 * 
 * All communication is handled through Serial and is abstracted to the Middleware Library MiddlewareLayer.
 *
 * @section install_sec Installation
 *
 * 1. [Clone the Repo](https://github.com/VFrancescon/coil_manipulator)
 * 
 * 2. `git submodule init`
 * 
 * 3. `git submodule update`
 * 
 * 4. `mkdir build && cd build`
 * 
 * 5. `sudo make`
 *
 * 6. `sudo make install`
 *
 * 7. Libraries are now installed onto the system and can be used from wherever in the system.
 *
 * 8. See src/ for examples.
 * 
 * 
 * @section psu_doc_remarks PSU Functions not Included
 * 
 * | Command | Function |
 * | :-----: | :------: |
 * | 0x25    | Read protection parameters  |
 * | 0x27    | Set protection paramters    |
 * | 0x29    | Set a new PSU Address       |
 * | 0x30    | Toggle local/remote control |
 * 
 * 
 * 
 */
