typedef unsigned long u64;

typedef struct {
    float x, y, w, h;
} Rect;

typedef struct {
    int r, g, b, a;
} Color;

typedef struct {
    char pad0[0x198];
    float unk198;
    float unk19C;
    char pad1A0[0x26C - 0x1A0];
    float unk26C;
    float unk270;
} Window;

extern void iosDlPushLayer(int);
extern void iosDlPopLayer(void);
extern void gsRegBegin(void);
extern void gsReg(int, u64);
extern void gsRegEnd(void);
typedef struct {
    unsigned short u;
    char pad2[2];
    unsigned short v;
} TexOrigin;

typedef struct {
    char pad0[0xC];
    TexOrigin *origin;
} TexInfo;

typedef struct {
    char pad0[0x20];
    TexInfo *info;
} Texture;

typedef struct {
    unsigned int r, g, b, a;
} UColor;

extern void texTransRequest(Texture *, int, int);
extern void texGetSize(Texture *, int *, int *);
extern void spriteDrawUVSensitive(int x, int y, int w, int h, int z, int u0, int v0, int u1, int v1, int r, int g, int b, int a);

#ifdef NONMATCHING
/* 2 diffs: the texture info pointer is loaded into v0 instead of v1 */
void windowSprite(Window *win, Rect r, UColor *col, Texture *tex, float z)
{
    int tw = 0;
    int th = 0;

    if (tex != 0) {
        TexOrigin *origin;
        iosDlPushLayer(0x1E);
        texTransRequest(tex, 3, 0);
        texGetSize(tex, &tw, &th);
        gsRegBegin();
        origin = tex->info->origin;
        gsReg(0x47, 0x30000);
        spriteDrawUVSensitive((int)(r.x + win->unk198 - win->unk26C * 0.5f), (int)(r.y + win->unk19C - win->unk270 * 0.5f),
                              (r.w != 0.0f) ? (int)r.w : (int)win->unk26C, (r.h != 0.0f) ? (int)r.h : (int)win->unk270, (int)z,
                              origin->u, origin->v, ((tw - 1) << 4) + origin->u, ((th - 1) << 4) + origin->v,
                              col->r >> 1, col->g >> 1, col->b >> 1, col->a);
        gsReg(0x47, 0x5140B);
        gsRegEnd();
        iosDlPopLayer();
    }
}
#endif
