#ifndef __TYPEDEFS__
#define __TYPEDEFS__

#include <stddef.h>   /* size_t */

typedef char *String;

typedef struct meta_data_s meta_data_t;
typedef String (*funcToString_t)();
typedef size_t (*funcGetNum_t)();
typedef void (*func_t)(); /* function's virual table */

struct meta_data_s {
	String name;
	size_t size;
	meta_data_t *super;
	func_t *v_table; /* pointer to array of pointers to function */
};



typedef enum objects { 
	OBJECT,
	ANIMAL,
	DOG,
	CAT,
	LEGENDARY_ANIMAL
}objects_t;

typedef enum funcs { 
	HASH_CODE,
	EQUALS,
	TO_STRING,
	FINALIZE,
	SAY_HELLO,
	SHOW_COUNTER,
	GET_NUM_MASTERS 
}funcs_t;

#endif /* __TYPEDEFS__ */
