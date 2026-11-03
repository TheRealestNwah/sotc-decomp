typedef struct { char pad[0x5B0]; int x5B0; } Boss;
typedef struct { char pad[0x398]; int x398; char pad2[0x3C50 - 0x39C]; int x3C50; } Game;
extern Boss *B_001A5A4C;
extern void func_000FB190(void);
static void *func_000FAEC8(Game *g)
{
    if (g->x3C50 != 1) return 0;
    if (g->x398 != 0 && B_001A5A4C != 0 && B_001A5A4C->x5B0 != 0) return 0;
    return func_000FB190;
}
