#ifdef NONMATCHING
/* Parked: 54 words differ (register allocation and scheduling) */
typedef struct {
    void *name;
    int id;
    float x;
    float y;
    float w;
    float h;
    int pad18[2];
    int r;
    int g;
    int b;
    int a;
    int i30, i34, i38, i3C, i40, i44, i48, i4C, i50, i54, i58;
    void *user;
    int i60;
    void *fn64;
    void *fn68;
    void *fn6C;
} __attribute__((aligned(8))) WinDesc;
typedef struct {
    char pad0[4];
    int id;
    char pad8[4];
    float x;
    float y;
    char *buf;
    int i18;
    int i1C;
    int len;
    int i24;
    char pad28[4];
    int win;
} Dlg;
extern char RO_0011B0F0[];
extern char *D_STR_00139728;
extern int D_00139B40;
extern int D_00139B44;
extern char rootPtn[];
extern void func_000D3890();
extern void func_000D3B80();
extern void func_000D4A38();
extern void *iosMallocAlign(void *, int, int);
extern int windowCreate(WinDesc, int, int);
extern int strlen(const char *);
void createStringInputDialog(Dlg *d, int parent)
{
    WinDesc tmp;
    WinDesc desc;

    desc.name = RO_0011B0F0;
    desc.id = d->id;
    desc.x = d->x;
    desc.y = d->y;
    desc.w = 214.0f;
    desc.h = 124.0f;
    desc.r = 0xC0;
    desc.g = 0xC0;
    desc.b = 0xC0;
    desc.a = 0x80;
    desc.i30 = 1;
    desc.i34 = 0;
    desc.i38 = 0;
    desc.i3C = 0;
    desc.i40 = 0;
    desc.i44 = 0;
    desc.i48 = 1;
    desc.i4C = 1;
    desc.i50 = 1;
    desc.i54 = 0;
    desc.i58 = 0;
    desc.user = d;
    desc.i60 = 0;
    desc.fn64 = func_000D3890;
    desc.fn68 = func_000D3B80;
    desc.fn6C = func_000D4A38;
    tmp = desc;
    d->buf = iosMallocAlign(rootPtn, 0x21, 0x10);
    d->i18 = 0;
    d->buf[0] = 0;
    d->win = windowCreate(tmp, parent, 1);
    d->i1C = 0;
    d->len = strlen(D_STR_00139728);
    d->i24 = 0;
    D_00139B44 = 0;
    D_00139B40 = 0;
}
#endif
