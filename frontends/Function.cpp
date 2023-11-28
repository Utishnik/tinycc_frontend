#include "tcc.h"

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


static int is_compatible_func(CType *type1, CType *type2)
{
    Sym *s1, *s2;

    s1 = type1->ref;
    s2 = type2->ref;
    if (s1->f.func_call != s2->f.func_call)
        return 0;
    if (s1->f.func_type != s2->f.func_type
        && s1->f.func_type != FUNC_OLD
        && s2->f.func_type != FUNC_OLD)
        return 0;
    for (;;) {
        if (!is_compatible_unqualified_types(&s1->type, &s2->type))
            return 0;
        if (s1->f.func_type == FUNC_OLD || s2->f.func_type == FUNC_OLD )
            return 1;
        s1 = s1->next;
        s2 = s2->next;
        if (!s1)
            return !s2;
        if (!s2)
            return 0;
    }
}

/* compare function types. OLD functions match any new functions */
static int is_compatible_func(CType *type1, CType *type2)
{
    Sym *s1, *s2;

    s1 = type1->ref;
    s2 = type2->ref;
    if (s1->f.func_call != s2->f.func_call)
        return 0;
    if (s1->f.func_type != s2->f.func_type
        && s1->f.func_type != FUNC_OLD
        && s2->f.func_type != FUNC_OLD)
        return 0;
    for (;;) {
        if (!is_compatible_unqualified_types(&s1->type, &s2->type))
            return 0;
        if (s1->f.func_type == FUNC_OLD || s2->f.func_type == FUNC_OLD )
            return 1;
        s1 = s1->next;
        s2 = s2->next;
        if (!s1)
            return !s2;
        if (!s2)
            return 0;
    }
}





