#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include <string.h> /* memcpy */

typedef enum type_s
{
    PT, MINIBUS, TAXI, ST, PC
} type_t;
void *new(int type, size_t size);

/************** PublicTransport ************************/

typedef struct PublicTransport_s PublicTransport_t;
typedef struct PT_members PT_members_t;
typedef struct PT_vtable_s PT_vtable_t;

int PT_get_ID(PublicTransport_t * const this);
void PT_display(PublicTransport_t * const this);
void PT_Ctor(PublicTransport_t * const this);
void PT_Dtor(PublicTransport_t * this);
void PT_CCtor(PublicTransport_t * this, const PublicTransport_t * const other);

/* static members */
int s_count = 0;
void print_count()
{
    printf("s_count: %d\n", s_count);
}

/* class members */
struct PT_members
{
    int m_license_plate;
};

/* class structure */
struct PublicTransport_s
{
    void *v_ptr;
    PT_members_t pt_members;
};

/* protected members */
int PT_get_ID(PublicTransport_t * const this)
{
    return this->pt_members.m_license_plate;
}

/* virtual methods */
void PT_display(PublicTransport_t * const this)
{
    printf("PublicTransport::display(): %d\n", this->pt_members.m_license_plate);
}

/* vtable */
struct PT_vtable_s
{
    void (*dtor)(PublicTransport_t *);
    void (*display)(PublicTransport_t *);
};

PT_vtable_t PT_vtable = { PT_Dtor, PT_display };

/* Ctor */
void PT_Ctor(PublicTransport_t * const this)
{
    /* set vtable */
    this->v_ptr = &PT_vtable;

    /* initialize variables */
    this->pt_members.m_license_plate = ++s_count;

    /* method body */
    printf("PublicTransport::Ctor()%d\n", this->pt_members.m_license_plate);
}

/* Dtor */
void PT_Dtor(PublicTransport_t * const this)
{
    /* method body */
    --s_count;
    printf("PublicTransport::Dtor()%d\n", this->pt_members.m_license_plate);
}

/* CCtor */
void PT_CCtor(PublicTransport_t * this, const PublicTransport_t * const other)
{
    /* set vtable */
    this->v_ptr = &PT_vtable;

    (void)other;

    /* initialize variables */
    this->pt_members.m_license_plate = ++s_count;

    /* method body */
    printf("PublicTransport::CCtor() %d\n", this->pt_members.m_license_plate);
}


/************** Minibus ************************/

typedef struct Minibus_members Minibus_members_t;
typedef struct Minibus_s Minibus_t;
typedef struct Minibus_vtable_s Minibus_vtable_t;

void wash(Minibus_t * const this, int minutes);
void Minibus_display(Minibus_t * const this);
void Minibus_Ctor(Minibus_t * const this);
void Minibus_Dtor(Minibus_t * const this);
void Minibus_CCtor(Minibus_t * const this, const Minibus_t * const other);

/* class members */
struct Minibus_members
{
    PT_members_t pt;
    int m_numSeats;
};

/* class structure */
struct Minibus_s
{
    void *v_ptr;
    Minibus_members_t minibus_members;
};

/* member methods */
void wash(Minibus_t * const this, int minutes)
{
    printf("Minibus::wash(%d) ID:%d\n", minutes, PT_get_ID((PublicTransport_t *)this));
}

/* virtual methods */
void Minibus_display(Minibus_t * const this)
{
    printf("Minibus::display() ID:%d", PT_get_ID((PublicTransport_t *)this));
    printf(" num seats:%d\n", this->minibus_members.m_numSeats);
}

/* vtable */
struct Minibus_vtable_s
{
    void (*dtor)(Minibus_t * const);
    void (*display)(Minibus_t * const);
    void (*wash)(Minibus_t * const, int);
};

Minibus_vtable_t Minibus_vtable = { Minibus_Dtor, Minibus_display, wash };

/* Ctor */
void Minibus_Ctor(Minibus_t * const this)
{
    /* call base ctor */
    PT_Ctor((PublicTransport_t *)this);

    /* set vtable */
    this->v_ptr = &Minibus_vtable;

    /* initialize variables */
    this->minibus_members.m_numSeats = 20;

    /* method body */
    printf("Minibus::Ctor()\n");
}

/* Dtor */
void Minibus_Dtor(Minibus_t * const this)
{
    printf("Minibus::Dtor()\n");

    /* call base dtor */
    PT_Dtor((PublicTransport_t *)this);
}

/* CCtor */
void Minibus_CCtor(Minibus_t * const this, const Minibus_t * const other)
{
    /* call base cctor */
    PT_CCtor((PublicTransport_t *)this, (PublicTransport_t *)other);

    /* set vtable */
    this->v_ptr = &Minibus_vtable;

    /* initialize variables */
    this->minibus_members.m_numSeats = other->minibus_members.m_numSeats;

    /* method body */
    printf("Minibus::CCtor()\n");
}

/******************* Taxi *****************************/
typedef struct Taxi_members_s Taxi_members_t;
typedef struct Taxi_s Taxi_t;
typedef struct Taxi_vtable_s Taxi_vtable_t;

void Taxi_display(Taxi_t * const this);
void Taxi_Ctor(Taxi_t * const this);
void Taxi_Dtor(Taxi_t * const this);
void Taxi_CCtor(Taxi_t * const this, const Taxi_t * const other);

/* class members */
struct Taxi_members_s
{
    PT_members_t pt;
};

/* class structure */
struct Taxi_s
{
    void *v_ptr;
    Taxi_members_t members;
};

/* virtual methods */
void Taxi_display(Taxi_t * const this)
{
    printf("Taxi::display() ID:%d\n", PT_get_ID((PublicTransport_t *)this));
}

/* vtable */
struct Taxi_vtable_s
{
    void (*dtor)(Taxi_t * const);
    void (*display)(Taxi_t * const);
};

Taxi_vtable_t Taxi_vtable = { Taxi_Dtor, Taxi_display };

/* Ctor */
void Taxi_Ctor(Taxi_t * const this)
{
    /* call base ctor */
    PT_Ctor((PublicTransport_t *)this);

    /* set vtable */
    this->v_ptr = &Taxi_vtable;
    
    /* method body */
    printf("Taxi::Ctor()\n");
}

/* Dtor */
void Taxi_Dtor(Taxi_t * const this)
{
    printf("Taxi::Dtor()\n");

    /* call base dtor */
    PT_Dtor((PublicTransport_t *)this);
}

/* CCtor */
void Taxi_CCtor(Taxi_t * const this, const Taxi_t * const other)
{
    /* call base cctor */
    PT_CCtor((PublicTransport_t *)this, (PublicTransport_t *)other);

    /* set vtable */
    this->v_ptr = &Taxi_vtable;

    /* method body */
    printf("Taxi::CCtor()\n");
}

/************************* SpecialTaxi ********************/
typedef struct ST_members_s ST_members_t;
typedef struct ST_s ST_t;
typedef struct ST_vtable_s ST_vtable_t;

void ST_display(ST_t * const this);
void ST_Ctor(ST_t * const this);
void ST_Dtor(ST_t * const this);
void ST_CCtor(ST_t * const this, const ST_t * const other);

/* class members */
struct ST_members_s
{
    Taxi_members_t taxi;
};

/* class structure */
struct ST_s
{
    void *v_ptr;
    ST_members_t members;
};

/* virtual methods */
void ST_display(ST_t * const this)
{
    printf("SpecialTaxi::display() ID:%d\n", PT_get_ID((PublicTransport_t *)this));
}

/* vtable */
struct ST_vtable_s
{
    void (*dtor)(ST_t * const);
    void (*display)(ST_t * const);
};

ST_vtable_t ST_vtable = { ST_Dtor, ST_display };

/* Ctor */
void ST_Ctor(ST_t * const this)
{
    /* call base ctor */
    Taxi_Ctor((Taxi_t *)this);

    /* set vtable */
    this->v_ptr = &ST_vtable;

    /* method body */
    printf("SpecialTaxi::Ctor()\n");
}

/* Dtor */
void ST_Dtor(ST_t * const this)
{
    printf("SpecialTaxi::Dtor()\n");

    /* call base dtor */
    Taxi_Dtor((Taxi_t *)this);
}

/* CCtor */
void ST_CCtor(ST_t * const this, const ST_t * const other)
{
    /* call base cctor */
    Taxi_CCtor((Taxi_t *)this, (Taxi_t *)other);

    /* set vtable */
    this->v_ptr = &ST_vtable;

    /* method body */
    printf("SpecialTaxi::CCtor()\n");
}

/****************** PublicConvoy ************************/
typedef struct PC_members_s PC_members_t;
typedef struct PC_s PC_t;
typedef struct PC_vtable_s PC_vtable_t;

void PC_display(PC_t * const t);
void PC_Ctor(PC_t * const this);
void PC_Dtor(PC_t * const this);
void PC_CCtor(PC_t * const this, const PC_t * const other);

/* class members */
struct PC_members_s
{
    PT_members_t pt;
    PublicTransport_t *m_pt1;
    PublicTransport_t *m_pt2;
    Minibus_t m_m;
    Taxi_t m_t;
};

/* class structure */
struct PC_s
{
    void *v_ptr;
    PC_members_t members;
};

/* virtual methods */
void PC_display(PC_t * const t)
{
    ((PT_vtable_t *)t->members.m_pt1->v_ptr)->display(t->members.m_pt1);
    ((PT_vtable_t *)t->members.m_pt2->v_ptr)->display(t->members.m_pt2);
    ((Minibus_vtable_t *)t->members.m_m.v_ptr)->display(&(t->members.m_m));
    ((Taxi_vtable_t *)t->members.m_t.v_ptr)->display(&(t->members.m_t));
}

/* vtable */
struct PC_vtable_s
{
    void (*dtor)(PC_t * const);
    void (*display)(PC_t * const);
};

PC_vtable_t PC_vtable = { PC_Dtor, PC_display };

/* Ctor */
void PC_Ctor(PC_t * const this)
{
    /* call base ctor */
    PT_Ctor((PublicTransport_t *)this);

    /* set vtable */
    this->v_ptr = &PC_vtable;

    /* initialize variables */
    this->members.m_pt1 = (PublicTransport_t *)new(MINIBUS, sizeof(Minibus_t));

    this->members.m_pt2 = (PublicTransport_t *)new(TAXI, sizeof(Taxi_t));

    Minibus_Ctor((Minibus_t *)this);
    Taxi_Ctor((Taxi_t *)this);
}

/* Dtor */
void PC_Dtor(PC_t * const this)
{
    PT_Dtor(this->members.m_pt1);
    free(this->members.m_pt1); this->members.m_pt1 = NULL;

    PT_Dtor(this->members.m_pt2);
    free(this->members.m_pt2); this->members.m_pt2 = NULL;

    /* PublicConvoy members dtors */
    Taxi_Dtor(&this->members.m_t);

    Minibus_Dtor(&this->members.m_m);

    /* call base dtor */
    PT_Dtor((PublicTransport_t *)this);
}

/* CCtor */
void PC_CCtor(PC_t * const this, const PC_t * const other)
{
    /* call base cctor */
    PT_CCtor((PublicTransport_t *)this, (PublicTransport_t *)other);

    /* set vtable */
    this->v_ptr = &PC_vtable;

    /* method body */
    this->members.m_pt1 = (PublicTransport_t *)new(MINIBUS, sizeof(Minibus_t));
    memcpy(this->members.m_pt1, other->members.m_pt1, sizeof(Minibus_t));

    this->members.m_pt2 = (PublicTransport_t *)new(TAXI, sizeof(Taxi_t));
    memcpy(this->members.m_pt2, other->members.m_pt2, sizeof(Taxi_t));

    memcpy(&this->members.m_m, &other->members.m_m, sizeof(Minibus_t));
    memcpy(&this->members.m_t, &other->members.m_t, sizeof(Taxi_t));
}

/************************* Global Functions ****************************/
void print_info_PT(PublicTransport_t * const a)
{
    ((PT_vtable_t *)a->v_ptr)->display(a);
}

void print_info_NoArg()
{
    print_count();
}

void print_info_Minibus(Minibus_t * const m)
{
    ((Minibus_vtable_t *)m->v_ptr)->wash(m, 3);
}

PublicTransport_t print_info_Int(int i)
{
    PublicTransport_t copy;
    Minibus_t ret;

    (void)i;

    Minibus_Ctor(&ret);
    printf("print_info(int i)\n");
    ((Minibus_vtable_t *)ret.v_ptr)->display(&ret);

    PT_CCtor(&copy, (PublicTransport_t *)&ret);
    Minibus_Dtor(&ret);
    return copy;
}

void taxi_display(Taxi_t s)
{
    Taxi_display(&s);
}

/* template */
int max_func(int a, int b)
{
    return a > b ? a : b;
}

/* auxillary functions */
void *new(int type, size_t size)
{
    void *obj = malloc(size);

    if (NULL == obj) exit(0);
    
    switch(type)
    {
        case PT:
            PT_Ctor((PublicTransport_t *)obj);
            break;
        case MINIBUS:
            Minibus_Ctor((Minibus_t *)obj);
            break;
        case TAXI:
            Taxi_Ctor((Taxi_t *)obj);
            break;
        case ST:
            ST_Ctor((ST_t *)obj);
            break;
        case PC:
            PC_Ctor((PC_t *)obj);
            break;
        default:
            return NULL;
    }
    return obj;
}

void destruct(void *this)
{
    PublicTransport_t *obj = (PublicTransport_t *)this;
    ((PT_vtable_t *)(*obj).v_ptr)->dtor(obj);
}

void delete(void *this)
{
    free(this); this = NULL;
}

#define ARRAY_SIZE (3)
int main()
{
    size_t i = 0;
    Minibus_t m;
    PublicTransport_t tmp;

    PublicTransport_t *array[ARRAY_SIZE];

    Minibus_t m_arr2;
    Taxi_t t_arr2;
    PublicTransport_t arr2[ARRAY_SIZE];

    Minibus_t m2;

    Minibus_t arr3[4];
    Taxi_t *arr4[4];

    ST_t st;
    Taxi_t st_copy;

    PC_t *ts1;
    PC_t *ts2;

    printf("%lu\n", sizeof(PublicTransport_t));
    printf("%lu\n", sizeof(Minibus_t));
    printf("%lu\n", sizeof(Taxi_t));
    printf("%lu\n", sizeof(ST_t));

    Minibus_Ctor(&m);
    print_info_Minibus(&m);

    tmp = print_info_Int(3);
    ((PT_vtable_t *)tmp.v_ptr)->display(&tmp);
    PT_Dtor(&tmp);
    
    array[0] = (PublicTransport_t *)new(MINIBUS, sizeof(Minibus_t));
    array[1] = (PublicTransport_t *)new(TAXI, sizeof(Taxi_t));
    array[2] = (PublicTransport_t *)new(MINIBUS, sizeof(Minibus_t));
    
    for (i = 0; i < ARRAY_SIZE; ++i)
    {
        ((PT_vtable_t *)(array[i]->v_ptr))->display(array[i]);
    }

    for (i = 0; i < ARRAY_SIZE; ++i)
    {
        ((PT_vtable_t *)(array[i]->v_ptr))->dtor(array[i]);
        delete(array[i]);
    }

    Minibus_Ctor(&m_arr2);
    PT_CCtor(&arr2[0], (PublicTransport_t *)&m_arr2);

    Taxi_Ctor(&t_arr2);
    PT_CCtor(&arr2[1], (PublicTransport_t *)&t_arr2);

    PT_Ctor(&arr2[2]);

    ((PT_vtable_t *)t_arr2.v_ptr)->dtor((PublicTransport_t *)&t_arr2);

    ((PT_vtable_t *)m_arr2.v_ptr)->dtor((PublicTransport_t *)&m_arr2);

    for (i = 0; i < ARRAY_SIZE; ++i)
    {
        ((PT_vtable_t *)(arr2[i].v_ptr))->display(&arr2[i]);
    }

    print_info_PT((PublicTransport_t *)&arr2[0]);

    print_count(); /* call to static function */

    Minibus_Ctor(&m2);

    print_count(); /* m2.print_count() - object call to static function */

    
    for (i = 0; i < 4; ++i)
    {
        Minibus_Ctor(&arr3[i]);
    }

    for (i = 0; i < 4; ++i)
    {
        arr4[i] = (Taxi_t *)new(TAXI, sizeof(Taxi_t));
    }

    for (i = 4; i > 0; --i)
    {
        ((PT_vtable_t *)arr4[i - 1]->v_ptr)->dtor((PublicTransport_t *)arr4[i - 1]);
        delete(arr4[i - 1]);
    }

    printf("%d\n", max_func(1, 2));
    printf("%d\n", max_func(1, 2.0f));
    
    ST_Ctor(&st);
    
    Taxi_CCtor(&st_copy, (Taxi_t *)&st);
    taxi_display(st_copy);
    Taxi_Dtor(&st_copy);
/*
    ts1 = (PC_t *)new(PC, sizeof(PC_t));
    ts2 = (PC_t *)malloc(sizeof(PC_t));
    PC_CCtor(ts2, ts1);
    ((PC_vtable_t *)ts1->v_ptr)->display(ts1);
    ((PC_vtable_t *)ts2->v_ptr)->display(ts2);
    ((PC_vtable_t *)ts1->v_ptr)->dtor(ts1);
    ((PC_vtable_t *)ts2->v_ptr)->display(ts2);
    ((PC_vtable_t *)ts2->v_ptr)->dtor(ts2);
*/
    (void)ts1;
    (void)ts2;
/************* Dtors not yet called ************/

    destruct(&st);

    for (i = 4; i > 0; --i)
    {
        destruct(&arr3[i - 1]);
    }

    destruct(&m2);

    for (i = ARRAY_SIZE; i > 0; --i)
    {
        destruct(&arr2[i - 1]);
    }

    destruct(&m);
}
