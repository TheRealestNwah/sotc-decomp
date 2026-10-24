/* Static predicates used by collision-query dispatch. */
static int func_000AE150(void *object, void *surface, void *point,
                         float *limit, float distance)
{
    return *limit <= distance ? 1 : 0;
}

static int func_000AE170(void *left, void *right)
{
    return left != right;
}
