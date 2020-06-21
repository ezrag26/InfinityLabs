#ifndef __logger_lib_H__ /* convention is to have it all in capital letters */
#define __logger_lib_H__ /* convention is to have it all in capital letters */
#include <stddef.h> /* add reason for using stddef */
enum action {stop, run, file_open_error };


int StrCmp( char *string1,  char *string2); /* remove space between '(' and 'char' */

int PrependCmp( char *string1,  char *string2); /* remove space between '(' and 'char' */

int AppendCmp( char *string1,  char *string2); /* remove space between '(' and 'char' */
/* the function names here don't follow the same format. Some say Fun.. and
      some say Func... Choose whichever one you want, but keep it consistent */
enum action FuncExit ();  /* remove space between function name and '()' */

enum action FuncRemove (); /* remove space between function name and '()' */

enum action FuncCount (); /* remove space between function name and '()' */

enum action FunPrepend (); /* remove space between function name and '()' */

enum action FunApepend (); /* remove space between function name and '()' */


#endif /* add a comment here with the same piece you have written next to the ifndef and define */
