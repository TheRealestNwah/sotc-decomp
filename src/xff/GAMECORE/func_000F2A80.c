typedef union {
    float f;
    char *p;
} Slot;

static void func_000F2A80(Slot *w0, Slot *p0, Slot *w1, Slot *p1, int idx, char *def, Slot *tbl, float scale)
{
    Slot *next = (Slot *)(idx * 4 + (int)tbl) + 1;

    if (idx == 0) {
        w0->f = ((Slot *)tbl[0].p)->f * scale;
        p0->p = tbl[0].p + 8;
        w1->f = ((Slot *)tbl[1].p)->f * scale;
        p1->p = tbl[1].p + 8;
    } else {
        w0->f = 1.0f;
        p0->p = def;
        w1->f = ((Slot *)next->p)->f * scale;
        p1->p = next->p + 8;
    }
}
