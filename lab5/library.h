#ifdef WIN
#ifdef LIB_EXPORTS
  #define SORTAPI __declspec(dllexport)
#else
  #define SORTAPI __declspec(dllimport)
#endif
#else
#ifdef LIB_EXPORTS
  #define SORTAPI
#else
  #define SORTAPI
#endif
#endif

#ifdef WIN
#define SORTCALL __cdecl
#else
#define SORTCALL
#endif

#include <gtk/gtk.h>
#include <glib/gstdio.h>
#include <stdio.h>
#include <math.h>

SORTAPI int SORTCALL main_form(int argc, char** argv);
