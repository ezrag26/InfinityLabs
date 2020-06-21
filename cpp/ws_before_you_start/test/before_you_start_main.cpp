#include <iostream>
#include <dlfcn.h>

#include "before_you_start.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    int i = 0;

    // func specified in command line argument (third argument)
    char *func_name = argv[2];

    // open the library
    cout << ++i << ". Opening library --> ";
    void* handle = dlopen("so/before_you_start.so", RTLD_LAZY);

    if (!handle) {
        cerr << " Cannot open library: " << dlerror() << '\n';
        return 1;
    }

    cout << " Library opened\n";

    // load the symbol
    typedef void (*func_t)();

    // reset errors
    dlerror();

    // get func symbol
    cout << ++i << ". Loading the symbol --> ";
    func_t func = (func_t) dlsym(handle, func_name);

    const char *dlsym_error = dlerror();
    if (dlsym_error) {
        cerr << " Cannot load symbol '" << func_name << "': " << dlsym_error <<
            '\n';
        dlclose(handle);
        return 1;
    }

    cout << " Symbol loaded\n";
    
    // invoke specified func
    cout << ++i << ". Invoking function --> ";
    func();

    // close the library
    cout << ++i << ". Closing library\n";
    dlclose(handle);

    return 0;
}