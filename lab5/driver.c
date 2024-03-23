#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main(int argc, char **argv) {
    void *handle;
    int (*form)(int, char**);
    char *error;
    handle = dlopen ("/lib/libform.so", RTLD_NOW);
    if (!handle) {
        fputs (dlerror(), stderr);
        exit(1);
    }
    form = dlsym(handle, "main_form");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    printf ("%d\n", (*form)(argc, argv));
    int dlc = dlclose(handle);
    if (dlc) {
    	fputs(dlerror(), stdout);
    }
    while(1) {
	    dlc++;
    }
    return 0;
}
