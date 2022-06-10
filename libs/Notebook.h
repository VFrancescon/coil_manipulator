/*! @page Notebook Notes
 *  @tableofcontents
 *  
 * @section Threads Multithreading on Unique Ptrs
 * 
 * Unique ptrs are safer to use than regular pointers. They are also more troublesome to multi-thread.
 * 
 * Here is a working method, still to be tested on the PSUs
 * 
 * @code {.cpp}
 * //declare in header
 * 
 * std::unique_ptr<ClassName> object;
 * 
 * //instantiate in source
 * 
 * object = std::make_unique<ClassName>(args);
 * 
 * //utilise as a thread
 * 
 * std::thread th(&ClassName::MethodName, object.get(), args);
 * 
 * @endcode
 * 
 * @note The std::unique_ptr::get() call is very important here.\n 
 * It returns the object that is pointed to and therefore allows us to thread stuff.
 * 
 * 
 * @section vcomports Virtual Com Ports
 * 
 * 
 * Process requires a bunch of terminals, so use Terminator. 
 * 
 * These terminals will be identified as TX at the start of each step, where X is a number.
 * 
 * 1. T0- `socat -d -d pty,raw,echo=0 pty,raw,echo=0`
 * 
 * 2. T1- `cat < /dev/pts/X`. X is the first output of step 1.
 * 
 * 3. T2- Optional. `echo "test" > /dev/pts[X+1]`
 * 
 * [Source](https://stackoverflow.com/questions/52187/virtual-serial-port-for-linux).
 * 
 * 
 * 
 */