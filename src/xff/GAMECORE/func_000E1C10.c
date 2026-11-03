typedef struct { char pad[0xD8]; float xD8; char pad2[0x564 - 0xDC]; int x564; } Cam;
static int func_000E1C10(Cam *c, float f)
{
    if (c->x564 == 0 && f <= c->xD8) return 1;
    return 0;
}
