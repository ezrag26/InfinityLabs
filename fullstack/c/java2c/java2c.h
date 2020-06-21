#ifndef __JAVA2C_H__
#define __JAVA2C_H__
/**************************** Function Definitions ****************************/
void ObjectCtor(object_t *object);
String ToString(object_t *this);
int Equals(object_t *this, object_t *compare_o);
int HashCode(object_t *this);
void Finalize(object_t *this);

void AnimalNoArgCtor(animal_t *animal);
void AnimalIntCtor(animal_t *animal, int num_masters);
void AnimalStaticInitializer();
static void AnimalSetDefaultValues(animal_t *animal);
static void AnimalInstanceVarsIntialization(animal_t *animal);
void AnimalSayHello(animal_t *this);
void AnimalShowCounter();
int AnimalGetNumMasters(animal_t *this);
String AnimalToString(animal_t *this);
void AnimalFinalize(animal_t *this);

void DogNoArgCtor(dog_t *dog);
void DogStaticInitializer();
static void DogSetDefaultValues(dog_t *this);
static void DogInstanceVarsInitialization(dog_t *this);
void DogSayHello(dog_t *this);
void DogFinalize(dog_t *this);
String DogToString(dog_t *this);

void CatStringCtor(cat_t *cat, String colors);
void CatNoArgCtor(cat_t *cat);
void CatStaticInitializer();
static void CatSetDefaultValues(cat_t *cat);
static void CatInstanceVarsInitialization(cat_t *cat);
void CatFinalize(cat_t *this);
String CatToString(cat_t *this);

void LegendaryAnimalNoArgCtor(legendary_animal_t *la);
void LegendaryAnimalStaticInitializer();
static void LegendaryAnimalSetDefaultValues(legendary_animal_t *la);
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

#endif /* __JAVA2C_H__ */
