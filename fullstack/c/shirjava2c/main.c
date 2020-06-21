#include <stdio.h>

#include "cfromjava.h"

/******************************************************************************/

void Foo(Animal_t *a)
{
	/* System.out.println(a.toString()); */
	printf("%s\n", ((funcToString_t)((Object_t *)a)->md->v_table[TO_STRING])(a));
}

int main()
{
/*	Object_t *obj = NULL;*/
	Animal_t *animal = (Animal_t *)alloc(GetMetaData(ANIMAL));
	Dog_t *dog = (Dog_t *)alloc(GetMetaData(DOG));
	Cat_t *cat = (Cat_t *)alloc(GetMetaData(CAT));
	LegendaryAnimal_t *la = (LegendaryAnimal_t *)
										   alloc(GetMetaData(LEGENDARY_ANIMAL));
	Animal_t *array[5] = {0};
	size_t i = 0;
	
	ObjectLoading();
	
	AnimalLoading();
	Animal_ctorDefault(animal);
	
	DogLoading();
	Dog_ctorDefault(dog);
	
	CatLoading();
	Cat_ctorDefault(cat);
	
	LegendaryLoading();
	Legendary_ctorDefault(la);
	
	(((Object_t *)animal)->md->v_table[SHOW_COUNTER])();
	
	printf("%lu\n", animal->ID);
	printf("%lu\n", ((Animal_t *)dog)->ID);
	printf("%lu\n", ((Animal_t *)cat)->ID);
	printf("%lu\n", ((Animal_t *)la)->ID);
	
	array[0] = ((Animal_t *)alloc(GetMetaData(DOG)));
	Dog_ctorDefault((Dog_t *)array[0]);
	array[1] = ((Animal_t *)alloc(GetMetaData(CAT)));
	Cat_ctorDefault((Cat_t *)array[1]);
	array[2] = ((Animal_t *)alloc(GetMetaData(CAT)));
	Cat_ctorString((Cat_t *)array[2], "white");
	array[3] = ((Animal_t *)alloc(GetMetaData(LEGENDARY_ANIMAL)));
	Legendary_ctorDefault((LegendaryAnimal_t *)array[3]);
	array[4] = ((Animal_t *)alloc(GetMetaData(ANIMAL)));
	Animal_ctorDefault(array[4]);

	for (i = 0; i < sizeof(array)/sizeof(array[0]); ++i)
	{
		Object_t *current = ((Object_t *)array[i]);
		current->md->v_table[SAY_HELLO](array[i]);
		printf("%lu\n", ((funcGetNum_t)current->md->v_table[GET_NUM_MASTERS])
																	(array[i]));
	}
	
	for (i = 0; i < sizeof(array)/sizeof(array[0]); ++i)
	{
		Foo(array[i]);
	}
	
	GC();
	printf("After gc\n");
	
	return 0;
}
