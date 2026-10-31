typedef struct {
    int pad0;
    float val;
} Item;

static int func_000813E8(Item *it)
{
    int r = 0;

    if (it->val < 9.01) {
        it->val = 9.01f;
        r = 1;
    }
    return r;
}
