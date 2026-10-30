extern long charrootdyn_getCollisionAttribute(void *geometry);

static int func_000415D0(void *geometry)
{
    if (charrootdyn_getCollisionAttribute(geometry) & 2) return 0; return 1;
}
