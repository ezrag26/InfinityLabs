#include <stdio.h>	/* printf 		*/
#include <string.h>	/* memset 		*/
#include <stdlib.h> /* alloc family */
#include <stddef.h> /* size_t		*/

#define BUFFER_SIZE (1024)
#define METADATA(obj) (((object_t *)obj)->metadata)
#define CALL(cast, obj, func) (((cast)METADATA(obj)->vtable[func])(obj))
#define SET_DEFAULT_VALS(obj) (memset((char *)obj + sizeof(object_t), 0, sizeof(obj) - sizeof(object_t)))


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

int counter = 0; /* equivalent to the static counter in the Java2c.java file */

typedef char* String;
typedef void (*vtable_t)();
typedef int (*func_ptr_int_t)();
typedef String (*func_ptr_str_t)();
typedef struct metadata_s metadata_t;
struct metadata_s
{
	String name;
	size_t size;
	metadata_t *super;
	vtable_t *vtable;
};

char string_buffer[BUFFER_SIZE];

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


/**************************** Function Definitions ****************************/
void ObjectCtor(object_t *object);
String ToString(object_t *this);
int Equals(object_t *this, object_t *compare_o);
int HashCode(object_t *this);
void Finalize(object_t *this);

void AnimalNoArgCtor(animal_t *animal);
void AnimalIntCtor(animal_t *animal, int num_masters);
static void AnimalStaticInitializer();
static void AnimalInstanceVarsIntialization(animal_t *animal);
void AnimalSayHello(animal_t *this);
void AnimalShowCounter();
int AnimalGetNumMasters(animal_t *this);
String AnimalToString(animal_t *this);
void AnimalFinalize(animal_t *this);

void DogNoArgCtor(dog_t *dog);
static void DogStaticInitializer();
static void DogInstanceVarsInitialization(dog_t *this);
void DogSayHello(dog_t *this);
void DogFinalize(dog_t *this);
String DogToString(dog_t *this);

void CatStringCtor(cat_t *cat, String colors);
void CatNoArgCtor(cat_t *cat);
static void CatStaticInitializer();
static void CatInstanceVarsInitialization(cat_t *cat);
void CatFinalize(cat_t *this);
String CatToString(cat_t *this);

void LegendaryAnimalNoArgCtor(legendary_animal_t *la);
static void LegendaryAnimalStaticInitializer();
static void LegendaryAnimalInstanceVarsInitialization(legendary_animal_t *la);
void LegendaryAnimalSayHello(legendary_animal_t *this);
void LegendaryAnimalFinalize(legendary_animal_t *this);
String LegendaryAnimalToString(legendary_animal_t *this);

/*********************************** VTables **********************************/

vtable_t object_vtable[] = {
	(vtable_t)ToString,
	(vtable_t)Equals,
	(vtable_t)HashCode,
	(vtable_t)Finalize
};

vtable_t animal_vtable[] = {
	(vtable_t)AnimalToString,
	(vtable_t)Equals,
	(vtable_t)HashCode,
	(vtable_t)AnimalFinalize,
	(vtable_t)AnimalSayHello,
	(vtable_t)AnimalShowCounter,
	(vtable_t)AnimalGetNumMasters
};

vtable_t dog_vtable[] = {
	(vtable_t)DogToString,
	(vtable_t)Equals,
	(vtable_t)HashCode,
	(vtable_t)DogFinalize,
	(vtable_t)DogSayHello,
	(vtable_t)AnimalShowCounter,
	(vtable_t)AnimalGetNumMasters
};

vtable_t cat_vtable[] = {
	(vtable_t)CatToString,
	(vtable_t)Equals,
	(vtable_t)HashCode,
	(vtable_t)CatFinalize,
	(vtable_t)AnimalSayHello,
	(vtable_t)AnimalShowCounter,
	(vtable_t)AnimalGetNumMasters
};

vtable_t la_vtable[] = {
	(vtable_t)LegendaryAnimalToString,
	(vtable_t)Equals,
	(vtable_t)HashCode,
	(vtable_t)LegendaryAnimalFinalize,
	(vtable_t)LegendaryAnimalSayHello,
	(vtable_t)AnimalShowCounter,
	(vtable_t)AnimalGetNumMasters
};

/********************************** MetaData **********************************/

metadata_t metadata_arr[] = {
	{"object_t", sizeof(object_t), NULL, object_vtable},
	{"animal_t", sizeof(animal_t), &metadata_arr[OBJECT], animal_vtable},
	{"dog_t", sizeof(dog_t), &metadata_arr[ANIMAL], dog_vtable},
	{"cat_t", sizeof(cat_t), &metadata_arr[ANIMAL], cat_vtable},
	{"legendary_animal_t", sizeof(legendary_animal_t), &metadata_arr[CAT],
																	la_vtable}
};

/********************************* ObjectFuncs ********************************/
void ObjectCtor(object_t *object)
{
	(void)object;
}

String ToString(object_t *this)
{
	sprintf(string_buffer,
			"%s@%d",
			METADATA(this)->name,
			CALL(func_ptr_int_t, this, HASH_CODE));

	return string_buffer;
}
int Equals(object_t *this, object_t *compare_o)
{
	return (this == compare_o);
}

int HashCode(object_t *this)
{
	return *(int *)&this;
}

void Finalize(object_t *this)
{
	free(this); this = NULL;
}

/********************************* AnimalFuncs ********************************/
void AnimalNoArgCtor(animal_t *animal)
{

	SET_DEFAULT_VALS(animal);
	ObjectCtor((object_t *)animal);
	AnimalInstanceVarsIntialization(animal);
	puts("Instance initialization block Animal");

	/* execute Ctor code */
	puts("Animal Ctor");
	animal->ID = ++counter;
	((object_t *)animal)->metadata->vtable[SAY_HELLO](animal);
	AnimalShowCounter();
	printf("%s\n", CALL(func_ptr_str_t, animal, TO_STRING));

	printf("%s\n", ((func_ptr_str_t)(&metadata_arr[OBJECT])->
					vtable[TO_STRING])(animal));
}

void AnimalIntCtor(animal_t *animal, int num_masters)
{
	SET_DEFAULT_VALS(animal);
	ObjectCtor((object_t *)animal);
	AnimalInstanceVarsIntialization(animal);
	puts("Instance initialization block Animal");

	/* execute Ctor code */
	puts("Animal Ctor int");
	animal->ID = ++counter;
	animal->num_masters = num_masters;
}

void AnimalStaticInitializer()
{
	puts("Static block Animal 1");
	puts("Static block Animal 2");
	counter = 0;
}

static void AnimalInstanceVarsIntialization(animal_t *animal)
{
	animal->num_legs = 5;
	animal->num_masters = 1;
}

String AnimalToString(animal_t *this)
{
	sprintf(string_buffer,
			"%s with ID: %d",
			METADATA(this)->name,
			this->ID);

	return string_buffer;
}

void AnimalFinalize(animal_t *this)
{
	printf("finalize Animal with ID:%d\n", this->ID);
	METADATA(this) = METADATA(this)->super;
	CALL(vtable_t, this, FINALIZE);
}

void AnimalSayHello(animal_t *this)
{
	puts("Animal Hello!");
	printf("I have %d legs\n", this->num_legs);
}

void AnimalShowCounter()
{
	printf("%d\n", counter);
}

int AnimalGetNumMasters(animal_t *this)
{
	return this->num_masters;
}

/********************************** DogFuncs **********************************/
void DogNoArgCtor(dog_t *dog)
{
	SET_DEFAULT_VALS(dog);
	AnimalIntCtor((animal_t *)dog, 2);
	DogInstanceVarsInitialization(dog);
	puts("Instance initialization block Dog");

	puts("Dog Ctor");
}

void DogStaticInitializer()
{
	puts("Static block Dog");
}

static void DogInstanceVarsInitialization(dog_t *this)
{
	this->num_legs = 4;
}

String DogToString(dog_t *this)
{
	sprintf(string_buffer,
			"%s with ID: %d",
			METADATA(this)->name,
			((animal_t *)this)->ID);

	return string_buffer;
}

void DogFinalize(dog_t *this)
{
	printf("finalize Dog with ID:%d\n", ((animal_t *)this)->ID);
	METADATA(this) = METADATA(this)->super;
	CALL(vtable_t, this, FINALIZE);
}

void DogSayHello(dog_t *this)
{
	puts("Dog Hello!");
	printf("I have %d legs\n", this->num_legs);
}

/********************************** CatFuncs **********************************/
void CatStringCtor(cat_t *cat, String colors)
{
	SET_DEFAULT_VALS(cat);
	AnimalNoArgCtor((animal_t *)cat);
	CatInstanceVarsInitialization(cat);

	cat->colors = colors;
	printf("Cat Ctor with color: %s\n", cat->colors);
}

void CatNoArgCtor(cat_t *cat)
{
	SET_DEFAULT_VALS(cat);
	CatInstanceVarsInitialization(cat);

	CatStringCtor(cat, "black");
	puts("Cat Ctor");
	cat->num_masters = 2;
}

void CatStaticInitializer()
{
	puts("Static block Cat");
}

static void CatInstanceVarsInitialization(cat_t *cat)
{
	cat->colors = NULL;
	cat->num_masters = 5;
}

String CatToString(cat_t *this)
{
	sprintf(string_buffer,
			"%s with ID: %d",
			METADATA(this)->name,
			((animal_t *)this)->ID);

	return string_buffer;
}

void CatFinalize(cat_t *this)
{
	printf("finalize Cat with ID:%d\n", ((animal_t *)this)->ID);
	METADATA(this) = METADATA(this)->super;
	CALL(vtable_t, this, FINALIZE);
}

/**************************** LegendaryAnimalFuncs ****************************/
void LegendaryAnimalNoArgCtor(legendary_animal_t *la)
{
	SET_DEFAULT_VALS(la);
	CatNoArgCtor((cat_t *)la);
	LegendaryAnimalInstanceVarsInitialization(la);

	puts("Legendary Ctor");
}

void LegendaryAnimalStaticInitializer()
{
	puts("Static block Legendary Animal");
}

static void LegendaryAnimalInstanceVarsInitialization(legendary_animal_t *la)
{
	(void)la;
}

String LegendaryAnimalToString(legendary_animal_t *this)
{
	sprintf(string_buffer,
			"%s with ID: %d",
			METADATA(this)->name,
			((animal_t *)this)->ID);

	return string_buffer;
}

void LegendaryAnimalFinalize(legendary_animal_t *this)
{
	printf("finalize LegendaryAnimal with ID:%d\n", ((animal_t *)this)->ID);
	METADATA(this) = METADATA(this)->super;
	CALL(vtable_t, this, FINALIZE);
}

void LegendaryAnimalSayHello(legendary_animal_t *this)
{
	(void)this;
	puts("Legendary Hello!");
}

/********************************** AllocMem *********************************/
static object_t *obj_array[10] = {NULL};
static int j = 0;

object_t *AllocMem(metadata_t *metadata)
{
	object_t *o = (object_t *)malloc(metadata->size);
	o->metadata = metadata;

	obj_array[j++] = o;

	return o;
}

/************************************ Main ************************************/

void Foo(animal_t *animal)
{
	printf("%s\n", CALL(func_ptr_str_t, animal, TO_STRING));
}

int main()
{
	size_t i = 0;

	object_t *obj = NULL;
    animal_t *animal = NULL;
    dog_t *dog = NULL;
    cat_t *cat = NULL;
    legendary_animal_t *la = NULL;
	animal_t *array[5] = {NULL};
	(void)obj;

	animal = (animal_t *)AllocMem(&metadata_arr[ANIMAL]);
	AnimalStaticInitializer();
	AnimalNoArgCtor(animal);

    dog = (dog_t *)AllocMem(&metadata_arr[DOG]);
	DogStaticInitializer();
	DogNoArgCtor(dog);

    cat = (cat_t *)AllocMem(&metadata_arr[CAT]);
	CatStaticInitializer();
	CatNoArgCtor(cat);

    la = (legendary_animal_t *)AllocMem(&metadata_arr[LEGENDARY]);
	LegendaryAnimalStaticInitializer();
	LegendaryAnimalNoArgCtor(la);

	AnimalShowCounter();

    printf("%d\n", animal->ID);
    printf("%d\n", ((animal_t *)dog)->ID);
    printf("%d\n", ((animal_t *)cat)->ID);
    printf("%d\n", ((animal_t *)la)->ID);

	/* equivalent to calling new in java file */
	array[0] = (animal_t *)AllocMem(&metadata_arr[DOG]);
	DogNoArgCtor((dog_t *)array[0]);

	array[1] = (animal_t *)AllocMem(&metadata_arr[CAT]);
	CatNoArgCtor((cat_t *)array[1]);

	array[2] = (animal_t *)AllocMem(&metadata_arr[CAT]);
	CatStringCtor((cat_t *)array[2], "white");

	array[3] = (animal_t *)AllocMem(&metadata_arr[LEGENDARY]);
	LegendaryAnimalNoArgCtor((legendary_animal_t *)array[3]);

	array[4] = (animal_t *)AllocMem(&metadata_arr[ANIMAL]);
	AnimalNoArgCtor(array[4]);

    for (i = 0; i < sizeof(array)/sizeof(array[0]); ++i)
	{
        CALL(vtable_t, array[i], SAY_HELLO);
        printf("%d\n", CALL(func_ptr_int_t, array[i], GET_NUM_MASTERS));
    }

    for (i = 0; i < sizeof(array)/sizeof(array[0]); ++i)
	{
        Foo(array[i]);
    }

	for (i = 0; obj_array[i] != NULL; ++i)
	{
		CALL(vtable_t, obj_array[i], FINALIZE); obj_array[i] = NULL;
	}

    puts("After gc");

	return 0;
}
