#include "tcc.h"

/*  original tcc
/* types */
#define VT_BTYPE       0x000f  /* mask for basic type */
#define VT_VOID             0  /* void type */
#define VT_BYTE             1  /* signed byte type */
#define VT_SHORT            2  /* short type */
#define VT_INT              3  /* integer type */
#define VT_LLONG            4  /* 64 bit integer */
#define VT_PTR              5  /* pointer */
#define VT_FUNC             6  /* function type */
#define VT_STRUCT           7  /* struct/union definition */
#define VT_FLOAT            8  /* IEEE float */
#define VT_DOUBLE           9  /* IEEE double */
#define VT_LDOUBLE         10  /* IEEE long double */
#define VT_BOOL            11  /* ISOC99 boolean type */                                                                                     #define VT_QLONG           13  /* 128-bit integer. Only used for x86-64 ABI */
#define VT_QFLOAT          14  /* 128-bit float. Only used for x86-64 ABI */

#define VT_UNSIGNED    0x0010  /* unsigned type */
#define VT_DEFSIGN     0x0020  /* explicitly signed or unsigned */
#define VT_ARRAY       0x0040  /* array type (also has VT_PTR) */
#define VT_BITFIELD    0x0080  /* bitfield modifier */
#define VT_CONSTANT    0x0100  /* const modifier */
#define VT_VOLATILE    0x0200  /* volatile modifier */
#define VT_VLA         0x0400  /* VLA type (also has VT_PTR and VT_ARRAY) */
#define VT_LONG        0x0800  /* long type (also has VT_INT rsp. VT_LLONG) */
*/
/* storage */
#define VT_EXTERN  0x00001000  /* extern definition */
#define VT_STATIC  0x00002000  /* static variable */

ST_INLN int is_float(int t)
{
   // int bt = t & VT_BTYPE;
    return bt == VT_LDOUBLE                                                                                                                          || bt == VT_DOUBLE
        || bt == VT_FLOAT
        || bt == VT_QFLOAT;
}

ST_INLN int is_integer_btype(int bt)
{
    return bt == VT_BYTE
        || bt == VT_BOOL
        || bt == VT_SHORT
        || bt == VT_INT
        || bt == VT_LLONG;
}

static int btype_size(int bt)
{
    return bt == VT_BYTE || bt == VT_BOOL ? 1 :
        bt == VT_SHORT ? 2 :
        bt == VT_INT ? 4 :
        bt == VT_LLONG ? 8 :
        bt == VT_PTR ? PTR_SIZE : 0;
}

/* returns function return register from type */
static int R_RET(int t)
{
    if (!is_float(t))
        return REG_IRET;
#ifdef TCC_TARGET_X86_64                                                                                                                         if ((t & VT_BTYPE) == VT_LDOUBLE)
        return TREG_ST0;
#elif defined TCC_TARGET_RISCV64
    if ((t & VT_BTYPE) == VT_LDOUBLE)
        return REG_IRET;
#endif
    return REG_FRET;
}

/* returns 2nd function return register, if any */
static int R2_RET(int t)
{
    t &= VT_BTYPE;
#if PTR_SIZE == 4
    if (t == VT_LLONG)
        return REG_IRE2;
#elif defined TCC_TARGET_X86_64
    if (t == VT_QLONG)
        return REG_IRE2;
    if (t == VT_QFLOAT)
        return REG_FRE2;
#elif defined TCC_TARGET_RISCV64
    if (t == VT_LDOUBLE)
        return REG_IRE2;
#endif
    return VT_CONST;
}





static inline CType *pointed_type(CType *type)
{
    return &type->ref->type;
}


static int compare_types(CType *type1, CType *type2, int unqualified)
{
    int bt1, t1, t2;

    t1 = type1->t & VT_TYPE;
    t2 = type2->t & VT_TYPE;
    if (unqualified) {
        /* strip qualifiers before comparing */
        t1 &= ~(VT_CONSTANT | VT_VOLATILE);
        t2 &= ~(VT_CONSTANT | VT_VOLATILE);
    }

    /* Default Vs explicit signedness only matters for char */
    if ((t1 & VT_BTYPE) != VT_BYTE) {
        t1 &= ~VT_DEFSIGN;
        t2 &= ~VT_DEFSIGN;
    }
    /* XXX: bitfields ? */
    if (t1 != t2)
        return 0;

    if ((t1 & VT_ARRAY)
        && !(type1->ref->c < 0
          || type2->ref->c < 0
          || type1->ref->c == type2->ref->c))
            return 0;

    /* test more complicated cases */
    bt1 = t1 & VT_BTYPE;
    if (bt1 == VT_PTR) {
        type1 = pointed_type(type1);
        type2 = pointed_type(type2);
        return is_compatible_types(type1, type2);
    } else if (bt1 == VT_STRUCT) {
        return (type1->ref == type2->ref);
    } else if (bt1 == VT_FUNC) {
        return is_compatible_func(type1, type2);
    } else if (IS_ENUM(type1->t) && IS_ENUM(type2->t)) {
        /* If both are enums then they must be the same, if only one is then
           t1 and t2 must be equal, which was checked above already.  */
        return type1->ref == type2->ref;
    } else {
        return 1;
    }
}

static int is_compatible_unqualified_types(CType *type1, CType *type2)
{
    return compare_types(type1,type2,1);
}
