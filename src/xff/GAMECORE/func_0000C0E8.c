typedef struct {
    char pad0[0x10];
    long f10;
    char pad18[0x100 - 0x18];
    long f100;
} GcGlobalVar;

extern GcGlobalVar gcGlobalVar;
extern long iosGetTCountExtension(void);
extern void func_0000B7C8(void);
extern void FlushPadHistory(void);
extern void func_0000BA70(void);
extern void graphFrameBufferReInitialize(void);

static void func_0000C0E8(void)
{
    gcGlobalVar.f10 = gcGlobalVar.f100;
    gcGlobalVar.f100 = iosGetTCountExtension();
    func_0000B7C8();
    FlushPadHistory();
    func_0000BA70();
    graphFrameBufferReInitialize();
}
