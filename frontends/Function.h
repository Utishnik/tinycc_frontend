#ifndef FUCN_FRONTEND
#define FUCN_FRONTEND

enum Base_FucntionTypes
{
    VOID,
    INT_32,
    INT_64,
    INT_16,
    INT_8,
    UINT_32,
    UINT_64,
    UINT_16,
    UINT_8,
    PTR
};

struct FuncAttr {
    unsigned
    func_call   : 3, /* calling convention (0..5), see below */
    func_type   : 2, /* FUNC_OLD/NEW/ELLIPSIS */
    func_noreturn : 1, /* attribute((noreturn)) */
    func_ctor   : 1, /* attribute((constructor)) */
    func_dtor   : 1, /* attribute((destructor)) */
    func_args   : 8, /* PE __stdcall args */
    func_alwinl : 1, /* always_inline */
    xxxx        : 15;
};


#endif