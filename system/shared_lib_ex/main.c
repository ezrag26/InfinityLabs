#include <stdio.h>
#include <dlfcn.h>
void foo();
void bar();
void baz();


int main()
{
	void (*func)();
  	void *handler = dlopen("libso2.so", RTLD_LAZY); /*Explicit Load*/
	foo();
	bar();
/*	baz();*/


  	if (handler)
  	{
    	*(void **)(&func) = dlsym(handler, "baz");
    	if(func)
    	{
      		(*func)(); /*Explicit Call*/
    	}
    	else
    	{
      		printf("baz() not found in libso2.so\n");
    	}
    	dlclose(handler);
  	}
  	else
  	{
	    printf("Unable to load libso2.so\n");
  	}

	return (0);
}
