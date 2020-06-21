typedef struct X_s
{
    int x;
} X_t;

typedef void (*func_t)(void *);

func_t X_Ctor(const void *this)
{
    printf("X Ctor\n");
}

func_t X_Dtor(const void *this)
{
    printf("X Dtor\n");
}

typedef struct Y_impl_s
{
    X_t m_x;
    int m_a;
} Y_impl_t;

typedef struct Y_s
{
    void *v_ptr;
    Y_impl_t y;
} Y_t;

void Y_Ctor(void *);
void Y_Dtor(void *);
void Y_Foo() {}
void Y_Bar();

struct vtable_y
{
    void (*Y_Foo)();
};

struct vtable_y y_vtable = 
{
    Y_Foo
};

void Y_Ctor(void *this)
{
    Y_t *obj = ((Y_t *)this);
    obj->v_ptr = &y_vtable; /* set vtable */

    X_Ctor(&obj->y.m_x); /* initialize variables */

    printf("Y_Ctor\n");
    
}

void Y_Dtor(void *this)
{
    Y_t *obj = ((Y_t *)this);

    printf("Y_Dtor\n");

    X_Dtor(&obj->y.m_x);
}

struct Der_impl
{
    Y_impl_t base;
    X_t m_x2;
};

typedef struct Der_s
{
    void *v_ptr;
    struct Der_impl der;
} Der_t;

void Der_Ctor(void *);
void Der_Dtor(void *);

void Der_Dodo() {}

struct vtable_Der
{
    void (*Der_Dodo)();
};

struct vtable_Der der_vtable = 
{
    Der_Dodo
};

void Der_Ctor(void *this)
{
    Der_t *obj = ((Der_t *)this);

    Y_Ctor(&obj->der.base);

    X_Ctor(&obj->der.m_x2); /* initialize variable */

    printf("Der_Ctor\n");

    obj->v_ptr = &der_vtable;
}

void Der_Dtor(void *this)
{
    Der_t *obj = ((Der_t *)this);
    
    printf("Der_Dtor\n");

    X_Dtor(&obj->der.m_x2);

    Y_Dtor(&obj->der.base);
}

int main()
{
    Y_t y1;
    Der_t d1;

    Y_Ctor(&y1);
    Der_Ctor(&d1);

    Der_Dtor(&d1);
    Y_Dtor(&y1);
}
