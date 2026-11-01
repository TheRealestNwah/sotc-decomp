typedef struct {
    int width;
    int height;
    float aspect;
    int pad0C;
    float dist;
    int pad14[2];
    float unk1C;
    float unk20;
    float unk24;
    float far;
    float near;
    float unk30;
} ViewContext;

typedef union {
    unsigned short h[2];
    int i;
} DCSize;

typedef struct {
    char pad[0x168];
    DCSize size;
} DC;

extern DC *iosGetCurrentDC(void);

static inline void SetDefaultViewContext(ViewContext *v, int width, int height)
{
    v->width = width;
    v->height = height;
    v->aspect = 0.94f;
    v->dist = 500.0f;
    v->unk1C = 2048.0f;
    v->unk20 = 2048.0f;
    v->unk24 = 0.25f;
    v->far = 16770000.0f;
    v->near = 0.05f;
    v->unk30 = 65536.0f;
}

void constructor_camera_context(ViewContext *v)
{
    DC *dc = iosGetCurrentDC();
    SetDefaultViewContext(v, dc->size.h[0], dc->size.h[1]);
}
