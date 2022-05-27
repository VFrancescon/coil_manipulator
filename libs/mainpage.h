/*! @mainpage Index Page
 *
 * @section intro_sec Introduction
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
 * 2. mkdir build && cd build
 * 
 * 3. sudo make
 *
 * 4. sudo make install
 *
 * 5. Libraries are now installed onto the system and can be used from whereever in the system.
 *
 * 6. See src/ for examples.
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