#include <stdio.h>      /* print */
#include <stdlib.h>     /* malloc */

typedef struct public_trasport PublicTransport;
typedef struct minibus Minibus;
typedef struct taxi Taxi;
typedef struct special_taxi SpecialTaxi;

typedef struct vtable_pt VTableForPT;
typedef struct vtable_mb VTableForMB;
typedef struct vtable_taxi VTableForTaxi;
typedef struct vtable_staxi VTableForSTaxi;

/* TODO: You could make a struct for each class that holds all of its data members,
where the first data member is its base's data members. This way if there was a
change the struct, you wouldn't have to change it in all the derived classes, just
in the 1 class's struct
- Obviously it is less important for this exercise because it's more of a hard-coded
exercise, and it would never be changed in the future, it's just something worth
noting */

struct public_trasport
{
    void* vptr;
    int m_licensePlate;
};

struct minibus
{
    void* vptr;
    int m_licensePlate;
    int m_numSeats;
};

struct taxi
{
    void* vptr;
    int m_licensePlate;
};

struct special_taxi
{
    void* vptr;
    int m_licensePlate;
};

/* TODO: I think the paramter for the virtual methods should NOT be
const ClassType * const, rather it should be ClassType * const. These methods
were not declared const and we can't assume that the variable won't be changed
in the method, even if it doesn't in our case */
struct vtable_pt
{
    void (*dtor)(PublicTransport* const);
    void (*display)(PublicTransport* const);
};
struct vtable_mb
{
    void (*dtor)(Minibus*);
    void (*display)(Minibus*const);
    void (*wash)( Minibus *const, int minuts);
};

struct vtable_taxi
{
    void (*dtor)(Taxi *const);
    void (*display)(Taxi *const);
};

struct vtable_staxi
{
    void (*dtor)(SpecialTaxi *const);
    void (*display)(SpecialTaxi *const);
};

/* TODO: All of your CCtors return its class type, but CCtors do not have return values */

void PublicTransportCtor(PublicTransport *const pt_);
void PublicTransportDtor(PublicTransport *const pt_);
void PublicTransportCCtor(PublicTransport *const pt_,
                                   const PublicTransport *const other_);
void PublicTransportDisplay(PublicTransport *const pt_);
void PublicTransportPrintCount(void);
int PublicTransportGetId(PublicTransport *const pt_);

void MinibusCtor(Minibus *const mb_);
void MinibusCCtor(Minibus* mb_, const Minibus *const other_);
void MinibusDtor(Minibus *const mb_);
void MinibusDisplay(Minibus *const mb_);
void MinibusWash(Minibus *const mb_, int minutes_);

void TaxiCtor(Taxi *const tx_);
void TaxiCCtor(Taxi *const tx_, const Taxi *const other_);
void TaxiDtor(Taxi *tx_);
void TaxiDisplay(Taxi *const tx_);

void SpecialTaxiCtor(SpecialTaxi *const st_);
void SpecialTaxiDtor(SpecialTaxi *const st_);
void SpecialTaxiCCtor(SpecialTaxi *st_, const SpecialTaxi *const other_);
void SpecialTaxiDisplay(SpecialTaxi *const st_);

PublicTransport PrintInfoPTRet(int i_);

/* TODO: I think the paramter should be just PublicTransport * const m_,
since the function was not declared as const. I don't think we can assume that
the variable won't be changed in the function */
void PrintInfoPT(PublicTransport *const m_);

/* TODO: same thing here */
void PrintInfoMB(Minibus *const m_);
void PrintInfo(void);
int MaxFuncInt(int t1, int t2);
void GlobalTaxiDisplay(Taxi s); /* TODO: I don't think const means anything here */

int g_publicTransportCount = 0;
VTableForPT g_vtableForPT = { PublicTransportDtor, PublicTransportDisplay };
VTableForMB g_vtableForMB = { MinibusDtor, MinibusDisplay, MinibusWash };
VTableForTaxi g_vtableForTaxi = { TaxiDtor, TaxiDisplay };
VTableForSTaxi g_vtableForSTaxi = { SpecialTaxiDtor ,SpecialTaxiDisplay  };

/* Public Trasport */
void PublicTransportCtor(PublicTransport *const pt_)
{
    pt_->vptr = (void *)&g_vtableForPT;
    pt_->m_licensePlate = ++g_publicTransportCount;
    printf("PublicTransport::Ctor()%d\n",pt_->m_licensePlate);
}

void PublicTransportCCtor(PublicTransport *const pt_,
                                    const PublicTransport *const other_)
{
    (void)other_;
    pt_->vptr = (void *)&g_vtableForPT;
    pt_->m_licensePlate = ++g_publicTransportCount;
    printf("PublicTransport::CCtor() %d\n",pt_->m_licensePlate);
}

void PublicTransportDtor(PublicTransport *const pt_)
{
    --g_publicTransportCount;
    printf("PublicTransport::Dtor()%d\n",pt_->m_licensePlate);
}

void PublicTransportDisplay(PublicTransport *const pt_)
{
    printf("PublicTransport::display(): %d\n",pt_->m_licensePlate);
}

void PublicTransportPrintCount(void)
{
    printf("s_count: %d\n", g_publicTransportCount);
}

int PublicTransportGetId(PublicTransport *const pt_)
{
    return (pt_->m_licensePlate);
}

/* Minibus */
void MinibusCtor(Minibus *const mb_)
{
    PublicTransportCtor((PublicTransport*)(mb_));
    mb_->m_numSeats = 20;
    ((PublicTransport *)mb_) -> vptr = (void *)&g_vtableForMB;
    printf("Minibus::Ctor()\n");
}

void MinibusCCtor(Minibus *const mb_, const Minibus *const other_)
{
    PublicTransportCCtor((PublicTransport*)(mb_),
                        (PublicTransport*)(other_));

    mb_->m_numSeats = other_->m_numSeats;
    ((PublicTransport *)mb_) -> vptr = (void *)&g_vtableForMB;
    printf("Minibus::CCtor()\n");
}

void MinibusDtor(Minibus *const mb_)
{
    printf("Minibus::Dtor()\n");
    PublicTransportDtor((PublicTransport*)(mb_));
}

void MinibusDisplay(Minibus *const mb_)
{
    int id = PublicTransportGetId((PublicTransport *)mb_);
    printf("Minibus::display() ID:%d", id );
    printf(" num seats:%d\n", mb_->m_numSeats );
}

void MinibusWash(Minibus *const mb_, int minutes_)
{
    int id = PublicTransportGetId((PublicTransport *)mb_);
    printf("Minibus::wash(%d) ID:%d\n", minutes_, id );
}

/* Taxi */

void TaxiCtor(Taxi *const tx_)
{
    PublicTransportCtor((PublicTransport*)(tx_));
    ((PublicTransport *)tx_) -> vptr = (void *)&g_vtableForTaxi;
    printf("Taxi::Ctor()\n");
}

void TaxiCCtor(Taxi *const tx_, const Taxi *const other_)
{
    PublicTransportCCtor((PublicTransport*)(tx_),
                (PublicTransport*)(other_));

    ((PublicTransport *)tx_) -> vptr = (void *)&g_vtableForTaxi;
    printf("Taxi::CCtor()\n");

}
void TaxiDtor(Taxi *const tx_)
{
    printf("Taxi::Dtor()\n");
    PublicTransportDtor((PublicTransport*)(tx_));
}

void TaxiDisplay(Taxi *const tx_)
{
    int id = PublicTransportGetId((PublicTransport *)tx_);
    printf("Taxi::display() ID:%d\n", id );
}

/* Special Taxi */

void SpecialTaxiCtor(SpecialTaxi *const st_)
{
    TaxiCtor((Taxi*)(st_));
    ((PublicTransport *)st_) -> vptr = (void *)&g_vtableForSTaxi;
    printf("SpecialTaxi::Ctor()\n");
}

void SpecialTaxiCCtor(SpecialTaxi *const st_, const SpecialTaxi *const other_)
{
    TaxiCCtor((Taxi*)(st_),
                (Taxi*)(other_));

    ((PublicTransport *)st_) -> vptr = (void *)&g_vtableForSTaxi;
    printf("SpecialTaxi::CCtor()\n");

}

void SpecialTaxiDtor(SpecialTaxi *const st_)
{
    printf("SpecialTaxi::Dtor()\n");
    TaxiDtor((Taxi*)(st_));
}

void SpecialTaxiDisplay(SpecialTaxi *const pt_)
{
    int id = PublicTransportGetId((PublicTransport *)pt_);
    printf("SpecialTaxi::display() ID:%d\n", id );
}

void PrintInfoPT(PublicTransport *const pt_)
{
    ((VTableForPT*)((pt_)->vptr))->display(pt_);
}

void PrintInfoMB(Minibus *const m_)
{
    ((VTableForMB*)((PublicTransport*)m_)->vptr)->wash(m_,3);
}

void PrintInfo(void)
{
    PublicTransportPrintCount();
}

PublicTransport PrintInfoPTRet(int i_)
{
    Minibus ret;
    PublicTransport translation_ret;

    (void)i_;

    MinibusCtor(&ret);
    printf("print_info(int i)\n");
    ((VTableForMB*)((PublicTransport*)&ret)->vptr)->display(&ret);

    PublicTransportCCtor(&translation_ret, (PublicTransport *)&ret);
    MinibusDtor(&ret);

    return (translation_ret);
}

void GlobalTaxiDisplay(Taxi s)
{
    ((VTableForTaxi *)(((PublicTransport*)&s)->vptr))->display(&s);
}


int MaxFuncInt(int t1, int t2)
{
    return ((t1 > t2) ? t1 : t2);
}

int main()
{
    Minibus m;
    PublicTransport FuncRet;
    PublicTransport *array[3];
    PublicTransport arr2[3];
    Minibus minibusArr2;
    Taxi taxiArr2;
    Minibus m2;
    Minibus arr3[4];
    Taxi *arr4[4];
    size_t i = 0;
    SpecialTaxi st;
    Taxi stToTaxi;

    MinibusCtor(&m);

    PrintInfoMB(&m);

    FuncRet = PrintInfoPTRet(3);
    ((VTableForPT*)(FuncRet.vptr))->display(&FuncRet);
    PublicTransportDtor(&FuncRet);

    array[0] = (PublicTransport*)malloc(sizeof(Minibus));
    MinibusCtor((Minibus*)array[0]);
    array[1] = (PublicTransport*)malloc(sizeof(Taxi));
    TaxiCtor((Taxi*)array[1]);
    array[2] = (PublicTransport*)malloc(sizeof(Minibus));
    MinibusCtor((Minibus*)array[2]);


    for (i = 0; i < 3; ++i) {
        ((VTableForPT*)(array[i]->vptr))->display(array[i]);
    }

    for (i = 0; i < 3; ++i) {
        ((VTableForPT*)(array[i]->vptr))->dtor(array[i]);
        free(array[i]);
    }

	MinibusCtor(&minibusArr2);
    PublicTransportCCtor(&arr2[0],(PublicTransport *)&minibusArr2);


    TaxiCtor(&taxiArr2);
    PublicTransportCCtor(&arr2[1],(PublicTransport *)&taxiArr2); /* TODO: I think the 2nd argument should be (PublicTransport *)&taxiArr2 */

    PublicTransportCtor(&arr2[2]);

	((VTableForPT*)(taxiArr2.vptr))->dtor((PublicTransport *)&taxiArr2);
    /*TaxiDtor(&taxiArr2);	*/										/* TODO: I think this call should be made dynamically, not statically */

	((VTableForPT*)(minibusArr2.vptr))->dtor((PublicTransport *)&minibusArr2);
    /*MinibusDtor(&minibusArr2); 		*/								/* TODO: I think this call should be made dynamically, not statically */

    for (i = 0; i < 3; ++i) {
        ((VTableForPT*)(arr2[i].vptr))->display(&arr2[i]);
    }

    PrintInfoPT(&arr2[0]);
    PublicTransportPrintCount();

    MinibusCtor(&m2);
    PublicTransportPrintCount();

    MinibusCtor(&arr3[0]);
    MinibusCtor(&arr3[1]);
    MinibusCtor(&arr3[2]);
    MinibusCtor(&arr3[3]);

    for (i = 0; i < 4; ++i)
    {
        arr4[i] = (Taxi*)malloc(sizeof(Taxi));
        TaxiCtor(arr4[i]);
    }
    for (i = 0; i < 4; ++i)
    {
		/*TaxiDtor(arr4[3-i]);*/ /* TODO: I think this call should be made dynamically, not statically */
		((VTableForPT*)(arr4[3-i]->vptr))->dtor((PublicTransport *)arr4[3-i]);
        free(arr4[3-i]);
    }

    printf("%d\n", MaxFuncInt(1, 2));
    printf("%d\n", MaxFuncInt(1, 2.0f));

    SpecialTaxiCtor(&st);
    TaxiCCtor(&stToTaxi, (Taxi *)&st); /* TODO: I think the 2nd argument should be (Taxi *)&st */
    GlobalTaxiDisplay(stToTaxi);
    TaxiDtor(&stToTaxi);


    /* Exit from scope - calling dtors */
	/* TODO: I think all the calls should be made dynamically, not statically */
	/*SpecialTaxiDtor(&st);*/
	((VTableForPT*)(st.vptr))->dtor((PublicTransport *)&st);
    for (i = 0; i < 4 ; i++)
    {
        /*MinibusDtor(&arr3[3-i]);*/
		((VTableForPT*)(arr3[3-i].vptr))->dtor((PublicTransport *)&arr3[3-i]);
    }

    /*MinibusDtor(&m2);*/
	((VTableForPT*)(m2.vptr))->dtor((PublicTransport *)&m2);

    for (i = 0; i < 3 ; i++)
    {
        /*PublicTransportDtor(&arr2[2-i]);*/
		((VTableForPT*)(arr2[2-i].vptr))->dtor((PublicTransport *)&arr2[2-i]);
    }
    /*MinibusDtor(&m);*/
	((VTableForPT*)(m.vptr))->dtor((PublicTransport *)&m);

    return (0);
}
