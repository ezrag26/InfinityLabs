typedef struct List {} List_t;
typedef struct Person {
    int age;
} Person_t;

void *ll_find(List_t *ll, int key)
{
    
}

void foo(List_t *ll, int key, int age)
{
    void *vv = ll_find(ll, key);

    Person_t *p = static_cast<Person_t *>(vv);
    p->age = age;
}