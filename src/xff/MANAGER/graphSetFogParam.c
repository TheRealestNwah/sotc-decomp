typedef struct {
    char pad[0xC];
    int r;
    int g;
    int b;
    float near;
    float far;
    int mode;
} GraphEnv;

typedef struct {
    long fog;
    char pad[0xA8];
} WorkBuf;

extern GraphEnv genv;
extern WorkBuf D_001358E0[];
extern int iosDlGetWorkBufId(void);

void graphSetFogParam(int r, int g, int b, int mode, float near, float far)
{
    genv.mode = mode;
    genv.near = near;
    genv.far = far;
    genv.g = g;
    genv.b = b;
    genv.r = r;
    D_001358E0[iosDlGetWorkBufId()].fog = r | ((long)g << 8) | ((long)b << 16);
}
