#include <stdio.h>  /* sprintf		 */
#include <stdlib.h> /* free & calloc */

#include "cfromjava.h"

char to_string[1000] = {0}; /* space for ToString functions */

/*----------------------------------------------------------------------------*/

size_t Equals(Object_t *obj1, Object_t *obj2);
String ToString(Object_t *obj);
void Finalize(Object_t *obj);
int HashCode(Object_t *obj);

static  func_t object_vtable[] = {(func_t)HashCode, 
								  (func_t)Equals, 
								  (func_t)ToString, 
								  (func_t)Finalize};
static meta_data_t object_md = {"Object",
							    sizeof(Object_t),
							    NULL,
							    object_vtable};

/*----------------------------------------------------------------------------*/

size_t AnimalGetNumMasters(Animal_t *animal);
String AnimalToString(Animal_t *animal);
void AnimalSayHello(Animal_t *animal);
void AnimalFinalize(Animal_t *animal);
void AnimalShowCounter();

static func_t animal_vtable[] = {(func_t)HashCode, 
								 (func_t)Equals, 
							 	 (func_t)AnimalToString,
							 	 (func_t)AnimalFinalize, 
						 		 (func_t)AnimalSayHello, 
						 		 (func_t)AnimalShowCounter, 
								 (func_t)AnimalGetNumMasters};		 
static meta_data_t animal_md = {"Animal",
								sizeof(Animal_t), 
								&object_md,
							 	animal_vtable};

/*----------------------------------------------------------------------------*/

String CatToString(Cat_t *cat);
void CatFinalize(Cat_t *cat);

static func_t cat_vtable[] = {(func_t)HashCode, 
							  (func_t)Equals,
							  (func_t)CatToString, 
							  (func_t)CatFinalize,
 							  (func_t)AnimalSayHello, 
 							  (func_t)AnimalShowCounter,
 							  (func_t)AnimalGetNumMasters};		 
static meta_data_t cat_md = {"Cat", 
							 sizeof(Cat_t), 
							 &animal_md,
						 	 cat_vtable};

/*----------------------------------------------------------------------------*/

String DogToString(Dog_t *dog);
void DogSayHello(Dog_t *dog);
void DogFinalize(Dog_t *dog);

static func_t dog_vtable[] = {(func_t)HashCode, 
							  (func_t)Equals,
 							  (func_t)DogToString, 
 							  (func_t)DogFinalize,
 							  (func_t)DogSayHello, 
 							  (func_t)AnimalShowCounter, 
 							  (func_t)AnimalGetNumMasters};	
static meta_data_t dog_md = {"Dog", 
							 sizeof(Dog_t), 
							 &animal_md,
							 dog_vtable};

/*----------------------------------------------------------------------------*/

String LegendaryToString(LegendaryAnimal_t *ls);
void LegendarySayHello(LegendaryAnimal_t *ls);
void LegendaryFinalize(LegendaryAnimal_t *ls);

static func_t legendary_vtable[] = {(func_t)HashCode, 
									(func_t)Equals,
  								    (func_t)LegendaryToString, 
									(func_t)LegendaryFinalize, 
									(func_t)LegendarySayHello, 
									(func_t)AnimalShowCounter, 
									(func_t)AnimalGetNumMasters};
static meta_data_t legendary_md = {"Legendary", 
								   sizeof(LegendaryAnimal_t), 
								   &cat_md,
								   legendary_vtable};


/******************************************************************************/
static Object_t *objects_to_free[100] = {0};
static size_t alloc_index = 0;

Object_t *alloc(meta_data_t *md)
{
	Object_t *obj = (Object_t *)calloc(1, md->size);
	obj->md = md;
	objects_to_free[alloc_index] = obj; /* save obj for GC Collector */
	++alloc_index;
	
	return obj;
}

void GC()
{
	size_t i = 0;
	
	for (i = 0; i < alloc_index; ++i)
	{
		objects_to_free[i]->md->v_table[FINALIZE](objects_to_free[i]);
	}
	
	alloc_index = 0;
}

meta_data_t *md_arr[] = {&object_md, &animal_md, &dog_md, &cat_md, &legendary_md};

meta_data_t *GetMetaData(objects_t object_type)
{
	return(md_arr[object_type]);
}

/******************************************************************************/



/******************************************************************************/
/**************************** OBJECT CLASS ************************************/

void ObjectLoading() {}

/*----------------------------------------------------------------------------*/

void Object_ctor(Object_t *obj)
{
	(void)obj;
}

/*----------------------------------------------------------------------------*/

int HashCode(Object_t *obj)
{
	return ((int)((size_t)obj));
}

/*----------------------------------------------------------------------------*/

size_t Equals(Object_t *obj1, Object_t *obj2)
{
	return (obj1 == obj2);
}

/*----------------------------------------------------------------------------*/

String ToString(Object_t *obj)
{
	sprintf(to_string, "%s@%d",obj->md->name, HashCode(obj));
	
	return to_string;
}

/*----------------------------------------------------------------------------*/

void Finalize(Object_t *obj)
{
	free(obj); obj = NULL;
}
/******************************************************************************/


/******************************************************************************/
/************************** ANIMAL CLASS **************************************/

static size_t counter = 0;

void AnimalLoading()
{
	/*	System.out.println("Static block Animal 1"); */
	printf("Static block Animal 1\n");
	printf("Static block Animal 2\n");
}

/*----------------------------------------------------------------------------*/

void Animal_ctorDefault(Animal_t *animal)
{
	Object_t *obj = (Object_t *)animal;
	
	animal->num_masters = 0; /* default value */
	animal->ID = 0;			 /* default value */
	
	Object_ctor(obj);
	
	animal->num_legs = 5;    /* initialization value */
	animal->num_masters = 1; /* initialization value */
	
	printf("Instance initialization block Animal\n");
	
	printf("Animal Ctor\n");
	
	animal->ID = ++counter;			  /* this.ID = ++counter; */
	obj->md->v_table[SAY_HELLO](obj); /* sayHello();    	  */
	obj->md->v_table[SHOW_COUNTER](); /* showCounter(); 	  */
	
	/* System.out.println(toString()); */
	printf("%s\n", ((funcToString_t)(obj->md->v_table[TO_STRING]))(animal)); 
	/* System.out.println(super.toString()); */
	printf("%s\n", ToString(obj));
}

/*----------------------------------------------------------------------------*/

void Animal_ctorInt(Animal_t *animal, size_t num_masters)
{
	Object_t *obj = (Object_t *)animal;
	
	animal->num_masters = 0; /* default value */
	animal->ID = 0;			 /* default value */
	
	Object_ctor(obj);
	
	animal->num_legs = 5;    /* initialization value */
	animal->num_masters = 1; /* initialization value */
	
	printf("Instance initialization block Animal\n");
	printf("Animal Ctor int\n");    /* System.out.println("Animal Ctor int"); */
	animal->ID = ++counter;	    	   /* this.ID = ++counter;  		      */
	animal->num_masters = num_masters; /* this.num_masters = num_masters;	  */
}

/*----------------------------------------------------------------------------*/

void AnimalSayHello(Animal_t *animal)
{
	/* System.out.println("Animal Hello!"); */
	printf("Animal Hello!\n"); 
	
	/* System.out.println("I have "+ num_legs + " legs"); */
	printf("I have %lu legs\n", animal->num_legs);
}

/*----------------------------------------------------------------------------*/

void AnimalShowCounter() 
{
	printf("%lu\n", counter); /* System.out.println(counter); */
}

/*----------------------------------------------------------------------------*/

size_t AnimalGetNumMasters(Animal_t *animal)
{
	return animal->num_masters; /* return this.num_masters; */
}

/*----------------------------------------------------------------------------*/

/* @Override */
String AnimalToString(Animal_t *animal)
{
	/* return "Animal with ID: " + ID; */
	sprintf(to_string, "Animal with ID: %lu", animal->ID);
	
	return to_string;
}

/*----------------------------------------------------------------------------*/

/* @Override */
void AnimalFinalize(Animal_t *animal)
{
	/* System.out.println("finalize Animal with ID:" + this.ID); */
	printf("finalize Animal with ID:%lu\n", animal->ID);
	
	/* ovverride meta data */
	((Object_t *)animal)->md = ((Object_t *)animal)->md->super;
	((Object_t *)animal)->md->v_table[FINALIZE](animal); /* super.finalize(); */
}
/******************************************************************************/


/******************************************************************************/
/*************************** CAT CLASS ****************************************/

void CatLoading()
{
	/*	System.out.println("Static block Cat"); */
	printf("Static block Cat\n");
}

/*----------------------------------------------------------------------------*/

void Cat_ctorDefault(Cat_t *cat)
{
	cat->num_masters = 0; 	      /* default value 					 */
	cat->colors = NULL;			  /* default value 					 */
	
	Cat_ctorString(cat, "black"); /* this("black"); 				 */
	
	printf("Cat ctor\n");         /* System.out.println("Cat Ctor"); */
	cat->num_masters = 2; 		  /* this.num_masters = 2;           */
	
}

/*----------------------------------------------------------------------------*/

void Cat_ctorString(Cat_t *cat, String colors)
{
	cat->num_masters = 0; /* default value 					 */
	cat->colors = NULL;   /* default value 					 */
	
	Animal_ctorDefault((Animal_t *)cat);
	
	cat->num_masters = 5; /* initialization value		     */
	
	cat->colors = colors; /* this.colors = colors; */
	/* System.out.println("Cat Ctor with color: " + this.colors); */
	printf("Cat Ctor with color: %s\n", cat->colors); 
}

/*----------------------------------------------------------------------------*/

/* @Override */
void CatFinalize(Cat_t *cat)
{
	/* System.out.println("finalize Cat with ID:" + this.ID); */
	printf("finalize Cat with ID:%lu\n", ((Animal_t *)cat)->ID);
	
	/* ovverride meta data */
	((Object_t *)cat)->md = ((Object_t *)cat)->md->super;
	((Object_t *)cat)->md->v_table[FINALIZE](cat); /* super.finalize(); */
}

/*----------------------------------------------------------------------------*/

/* @Override */
String CatToString(Cat_t *cat)
{
	/* return "Cat with ID: " + ID; */
	sprintf(to_string, "Cat with ID: %lu", ((Animal_t *)cat)->ID);
	
	return to_string;
}
/******************************************************************************/


/******************************************************************************/
/*************************** DOG CLASS ****************************************/

void DogLoading()
{
	/*	System.out.println("Static block Dog"); */
	printf("Static block Dog\n");
}

/*----------------------------------------------------------------------------*/

void Dog_ctorDefault(Dog_t *dog)
{
	dog->num_legs = 0; 					   /* default value                   */
	
	Animal_ctorInt((Animal_t *)dog, 2);    /* super(2);                       */
	
	dog->num_legs = 4; 					   /* initialization value			  */
	
	printf("Instance initialization block Dog\n");
	printf("Dog ctor\n");      			   /* System.out.println("Dog Ctor"); */ 
}

/*----------------------------------------------------------------------------*/

void DogSayHello(Dog_t *dog)
{
	/* System.out.println("Dog Hello!"); */
	printf("Dog Hello!\n"); 
	
	/* System.out.println("I have "+ num_legs + " legs"); */
	printf("I have %lu legs\n", dog->num_legs);
}

/*----------------------------------------------------------------------------*/

/* @Override */
void DogFinalize(Dog_t *dog)
{
	/* System.out.println("finalize Dog with ID:" + this.ID); */
	printf("finalize Dog with ID:%lu\n", ((Animal_t *)dog)->ID);
	
	/* ovverride meta data */
	((Object_t *)dog)->md = ((Object_t *)dog)->md->super;
	((Object_t *)dog)->md->v_table[FINALIZE](dog); /* super.finalize(); */
}

/*----------------------------------------------------------------------------*/

/* @Override */
String DogToString(Dog_t *dog)
{
	/* return "Dog with ID: " + ID; */
	sprintf(to_string, "Dog with ID: %lu", ((Animal_t *)dog)->ID);
	
	return to_string;
}
/******************************************************************************/



/******************************************************************************/
/*************************** LENGENDARY CLASS *********************************/

void LegendaryLoading()
{
	/*	System.out.println("Static block Legendary Animal"); */
	printf("Static block Legendary Animal\n");
}

/*----------------------------------------------------------------------------*/

void Legendary_ctorDefault(LegendaryAnimal_t *la)
{
	Cat_ctorDefault((Cat_t *)la);
	printf("Legendary Ctor\n"); /* System.out.println("Legendary Ctor"); */
}

/*----------------------------------------------------------------------------*/

void LegendarySayHello(LegendaryAnimal_t *la)
{
	(void)la;
	/* System.out.println("Legendary Hello!"); */
	printf("Legendary Hello!\n"); 
}

/*----------------------------------------------------------------------------*/

/* @Override */
void LegendaryFinalize(LegendaryAnimal_t *la)
{
	/* System.out.println("finalize LegendaryAnimal with ID:" + this.ID); */
	printf("finalize LegendaryAnimal with ID:%lu\n", ((Animal_t *)la)->ID);
	
	/* ovverride meta data */
	((Object_t *)la)->md = ((Object_t *)la)->md->super;
	((Object_t *)la)->md->v_table[FINALIZE](la); /* super.finalize(); */
}

/*----------------------------------------------------------------------------*/

/* @Override */
String LegendaryToString(LegendaryAnimal_t *la)
{
	/* return "LegendaryAnimal with ID: " + ID; */
	sprintf(to_string, "LegendaryAnimal with ID: %lu", (((Animal_t *)la)->ID));
	
	return to_string;
}

/******************************************************************************/


