# define LIBTCCAPI

LIBTCCAPI void tcc_set_error_func(TCCState *s, void *error_opaque, TCCErrorFunc error_func)
{
    s->error_opaque = error_opaque;
    s->error_func = error_func;
}

LIBTCCAPI TCCErrorFunc tcc_get_error_func(TCCState *s)
{
    return s->error_func;
}

LIBTCCAPI void *tcc_get_error_opaque(TCCState *s)
{
    return s->error_opaque;
}