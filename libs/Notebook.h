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
 */