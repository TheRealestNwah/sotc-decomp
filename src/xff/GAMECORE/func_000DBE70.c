typedef struct {
    int f0;
    float f4;
} Item;

static int func_000DBE70(Item **a, Item **b)
{
    if ((*a)->f4 > (*b)->f4) {
        return 1;
    }
    return -1;
}
