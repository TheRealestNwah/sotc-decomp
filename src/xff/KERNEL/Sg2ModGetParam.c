typedef struct { int unk0; int a; int b; } ModPair;
typedef struct { char pad0[0x30]; ModPair pair; int x3C; int x40; char pad44[0x96C]; } Mod;
extern Mod B_000C5C18[];

#ifdef NONMATCHING
/* Parked: 2 words differ (final return: original fills the jr delay slot with v0 = 0; ours emits it before jr) */
int Sg2ModGetParam(int port, int type, int *a, int *b)
{
    switch (type) {
    case 1: {
        register char *base __asm__("$4") = (char *)B_000C5C18;
        register ModPair *p __asm__("$5");
        __asm__("" : "+r"(base));
        { register int o __asm__("$2") = port * (int)sizeof(Mod) + 0x30; __asm__("" : "+r"(o)); p = (ModPair *)(base + o); __asm__("" : "+r"(p)); }
        {
            register ModPair *q __asm__("$4") = p;
            __asm__("" : "+r"(q));
            *a = p->a;
            *b = q->b;
        }
        break;
    }
    case 4:
        *a = B_000C5C18[port].x3C;
        break;
    case 8:
        *a = B_000C5C18[port].x40;
        break;
    }
    return 0;
}
#endif
