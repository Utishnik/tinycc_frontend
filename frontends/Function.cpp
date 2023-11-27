#include "tcc.h"

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





