#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__
typedef enum funcs
{
	TO_STRING,
	EQUALS,
	HASH_CODE,
	FINALIZE,
	SAY_HELLO,
	SHOW_COUNTER,
	GET_NUM_MASTERS
} funcs_t;

typedef enum class_meta
{
	OBJECT,
	ANIMAL,
	DOG,
	CAT,
	LEGENDARY
} class_meta_t;
typedef char* String;
typedef void (*vtable_t)();
typedef struct metadata_s metadata_t;
struct metadata_s
{
	String name;
	size_t size;
	metadata_t *super;
	vtable_t *vtable;
};
/*********************************** Classes **********************************/
typedef struct object_s
{
	metadata_t *metadata;
} object_t;

typedef struct animal_s
{
	object_t object;
	int num_legs;
	int num_masters;
	int ID;
} animal_t;

typedef struct dog_s
{
	animal_t animal;
	int num_legs;
} dog_t;

typedef struct cat_s
{
	animal_t animal;
	String colors;
	int num_masters;
} cat_t;

typedef struct legendary_animal_s
{
	cat_t cat;
} legendary_animal_t;

#endif /* __TYPEDEF_H__ */
