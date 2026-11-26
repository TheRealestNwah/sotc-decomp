extern struct { char pad[0x168]; float f; } gcGlobalVar;
extern struct { int unk0[7]; } B_0018B6A8;
extern int B_0018B6B8;
extern char RO_0017E098[], RO_0017E0B8[], RO_0017E118[], RO_0017E130[], RO_0017E148[];
extern int *D_0017ADE0[];
extern void (*D_0017ADA8[])(int);
extern int MakeStrHashValue(const char *);
extern int SpriteMenuGetLayerNoByHash(void *, int);
extern int SpriteMenuGetSelectLayer(void *);
extern int SpriteMenuGetPadEvent(void *);
extern void SpriteMenuSetDispFlag(void *, int, int);
extern void SpriteMenuSetLayer(void *, int);
extern void SpriteMenuSetSelectSubMenuId(void *, int);
extern void controllerAlertDisable(int);
extern int *getProgressiveMode(void);
extern void graphFrameBufferReInitializeRequest(void);
extern void iosGsChangeScreenOffset(void);

typedef struct {
    char pad0[0x10];
    unsigned int flags;
    int idx;
    int val;
} MenuPart;

typedef struct {
    MenuPart *part;
    char pad4[0xC];
    union { float f; int i; } alpha;
    char pad14[0x8];
} MenuItem;

typedef struct {
    int unk0;
    MenuItem *items;
    unsigned int type : 4;
    unsigned int n : 10;
    char padC[0x38];
} MenuGroup;

typedef struct {
    int unk0;
    MenuGroup *groups;
    int unk8;
    int cur;
} MenuInfo;

#define LAYER(m, s) SpriteMenuGetLayerNoByHash(m, MakeStrHashValue(s))

#ifdef NONMATCHING /* 10 diffs: the 15-second close loads gcGlobalVar.f before the work[4] store and swaps the 3.0f/1.0f registers */
/* Option menu update: dims unselected values on the top page, moves the screen offset on the position page (clamped
   to +-10) and closes the progressive-scan test after 15 seconds. */
static void func_00073F70(void *menu, MenuInfo *info, int *work)
{
    if (SpriteMenuGetSelectLayer(menu) == LAYER(menu, RO_0017E098)) {
        MenuGroup *g = &info->groups[info->cur];
        int i;

        if (g->type) {
            for (i = 0; i < g->n; i++) {
                MenuItem *it = &g->items[i];
                MenuPart *p = it->part;
                if (p->idx != -1 && p->val != -1 && !(p->flags & 0x100)) {
                    int *v = D_0017ADE0[p->idx];
                    if (v) {
                        it->alpha.f = (*v == p->val) ? 1.0f : 0.5f;
                    }
                }
            }
        }
    } else if (SpriteMenuGetSelectLayer(menu) == LAYER(menu, RO_0017E0B8)) {
        int pad = SpriteMenuGetPadEvent(menu);
        int x = work[1];
        int y = work[2];

        if (pad & 4)
            work[2]--;
        if (pad & 8)
            work[2]++;
        if (pad & 0x10)
            work[1]--;
        if (pad & 0x20)
            work[1]++;
        if (B_0018B6A8.unk0[1] + work[1] < -10)
            work[1] = -10 - B_0018B6A8.unk0[1];
        if (B_0018B6A8.unk0[1] + work[1] > 10)
            work[1] = 10 - B_0018B6A8.unk0[1];
        if (B_0018B6A8.unk0[2] + work[2] < -10)
            work[2] = -10 - B_0018B6A8.unk0[2];
        if (B_0018B6A8.unk0[2] + work[2] > 10)
            work[2] = 10 - B_0018B6A8.unk0[2];
        D_0017ADA8[1](B_0018B6A8.unk0[1] + work[1]);
        D_0017ADA8[2](B_0018B6A8.unk0[2] + work[2]);
        if (x != work[1] || y != work[2])
            iosGsChangeScreenOffset();
    } else if (SpriteMenuGetSelectLayer(menu) == LAYER(menu, RO_0017E148)) {
    } else if (SpriteMenuGetSelectLayer(menu) == LAYER(menu, RO_0017E118)) {
    } else if (SpriteMenuGetSelectLayer(menu) == LAYER(menu, RO_0017E130)) {
        if (gcGlobalVar.f - *(float *)&work[6] >= 15.0f) {
            controllerAlertDisable(0);
            SpriteMenuSetDispFlag(menu, LAYER(menu, RO_0017E130), 0);
            SpriteMenuSetLayer(menu, LAYER(menu, RO_0017E098));
            work[4] &= -5;
            *(float *)&work[5] = gcGlobalVar.f - 3.0f + 1.0f;
            if (*getProgressiveMode() != 0) {
                *getProgressiveMode() = 0;
                graphFrameBufferReInitializeRequest();
            }
            B_0018B6B8 = 0;
            SpriteMenuSetSelectSubMenuId(menu, 0);
        }
    }
}
#endif
