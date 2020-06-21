#include <dlfcn.h>

#include "q11.hpp"
// #include "q11.h"

int main()
{
    int i = 1;
    int c = 'a';
    int *pInt = &i;
    float f = 1.5;
    unsigned char uc = 200;
    // Foo();
    // Foo(i);
    // Foo(c);
    // Foo(pInt);
    // Foo(NULL);
    // Foo(f);
    // Foo(uc);

    // void *handle = dlopen("ws1/so/q11.so", RTLD_LAZY);

    // if (!handle) return 1;
    
    // typedef void (* func_t)(char c);

    // dlerror();

    // func_t func = (func_t) dlsym(handle, "__Z3Fooc");

    // const char *dlsym_error = dlerror();
    // if (dlsym_error) {
    //     dlclose(handle);
    //     return 1;
    // }

    // // func();
    // // func(1);
    // func('a');

}
