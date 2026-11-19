typedef struct { int a, b, c, d; } FontParam;
typedef struct { int pad0; int pad1; int id; int pad3; FontParam p; } Font;
typedef struct {
    int enabled;
    int f4;
    int f8;
    int pad;
    unsigned int col0[16];
    unsigned int col1[16];
    float r, g, b, a;
} KState;

extern KState D_001359F0;
extern int D_00135B40;
extern const FontParam RO_0013CD70;
extern const float RO_0013CE88[16];
extern const float RO_0013CEC8[16];
extern const float RO_0013CF08[16];
extern int iosEntryLocaleFontNoLoad(int, Font *);
extern void func_00016038(void);

#define F2U(x) ((unsigned int)((x) * 255.0f))

void kInit(void)
{
    Font f;
    int i;

    f.p.a = RO_0013CD70.a;
    f.p.b = RO_0013CD70.b;
    f.p.c = RO_0013CD70.c;
    f.p.d = RO_0013CD70.d;
    D_001359F0.f4 = 0;
    f.id = iosEntryLocaleFontNoLoad(D_00135B40, &f);
    for (i = 0; i < 16; i++) {
        D_001359F0.col0[i] = (F2U(RO_0013CF08[i]) << 24) | (F2U(RO_0013CE88[i]) | (F2U(RO_0013CE88[i]) << 16) | (F2U(RO_0013CE88[i]) << 8));
    }
    for (i = 0; i < 16; i++) {
        D_001359F0.col1[i] = (F2U(RO_0013CF08[i]) << 24) | (F2U(RO_0013CEC8[i]) | (F2U(RO_0013CEC8[i]) << 16) | (F2U(RO_0013CEC8[i]) << 8));
    }
    D_001359F0.f8 = 0;
    D_001359F0.r = D_001359F0.g = D_001359F0.b = D_001359F0.a = 1.0f;
    func_00016038();
    D_001359F0.enabled = 1;
}
