typedef struct { int w[0x50 / 4]; } S50;
typedef struct { int w[0x68 / 4]; } S68;
typedef struct { int w[0x190 / 4]; } S190;
typedef struct { int w[0x320 / 4]; } S320;
typedef struct { long w[0x70 / 8]; } S70;
extern S50 B_00183EF0;
extern S68 B_00183F40;
extern S190 B_00183FA8;
extern S320 B_00184138;
extern S320 B_00184458;
extern S70 B_00184778;

void gameFlagCheckPointLoad(S50 *a, S68 *b, S190 *c, S320 *d, S320 *e, S70 *f)
{
    B_00183EF0 = *a;
    B_00183F40 = *b;
    B_00183FA8 = *c;
    B_00184138 = *d;
    B_00184458 = *e;
    B_00184778 = *f;
}
