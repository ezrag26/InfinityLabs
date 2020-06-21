#ifndef __C_FROM_JAVA__
#define __C_FROM_JAVA__

#include <stdlib.h> /* free & calloc */

#include "typedefs.h"


/************************** OBJECT CLASS **************************************/

typedef struct Object_s {
	meta_data_t *md;
}Object_t;

void Object_ctor(Object_t *obj);
void ObjectLoading();

/******************************************************************************/

/************************** ANIMAL CLASS **************************************/

typedef struct Animal_s {
	Object_t object;
	size_t num_legs;    /* private */
	size_t num_masters; /* private */
	size_t ID;
}Animal_t;

void Animal_ctorInt(Animal_t *animal, size_t num_masters);
void Animal_ctorDefault(Animal_t *animal);
void AnimalLoading();

/******************************************************************************/

/*************************** CAT CLASS ****************************************/

typedef struct Cat_s {
	Animal_t animal;
	String colors;
	size_t num_masters;
}Cat_t;

void Cat_ctorString(Cat_t *cat, String colors);
void Cat_ctorDefault(Cat_t *cat);
void CatLoading();

/******************************************************************************/

/*************************** DOG CLASS ****************************************/

typedef struct Dog_s {
	Animal_t animal;
	size_t num_legs;
}Dog_t;

void Dog_ctorDefault(Dog_t *dog);
void DogLoading();

/******************************************************************************/

/*************************** LENGENDARY CLASS *********************************/

typedef struct LegendaryAnimal_s {
	Cat_t cat;
}LegendaryAnimal_t;


void Legendary_ctorDefault(LegendaryAnimal_t *ls);
void LegendaryLoading();

/******************************************************************************/

/* Releases all the alloc() memory */
void GC();
Object_t *alloc(meta_data_t *md);
meta_data_t *GetMetaData(objects_t object_type);


#endif /* __C_FROM_JAVA__ */
