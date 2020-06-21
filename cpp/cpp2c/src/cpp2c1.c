#include <stdio.h> /* printf */

typedef struct X_s
{
    int x;
} X_t;

typedef void (*func_t)(void *);

func_t X_Ctor(const void *this)
{
    /* printf("In Ctor\n"); */
    /* printf("this->x = %d\n", this->x); */
}
func_t X_Dtor(const void *this)
{
    /* printf("In Dtor\n"); */
}

/* func_t CCtor(void *other); */

int main()
{
    X_t x1;
    X_Ctor(&x1);
    X_Dtor(&x1);
}
