typedef int s128 __attribute__((mode(TI)));

typedef struct {
    int chara;
    int unk4;
    char *geo;
    char *pos;
    int unk10;
    int index;
} HeadCtrl;

extern int D_0017B8C8;
extern s128 ZeroVector;
extern char B_001A5B50[];
extern char *GetSCRCharaAIWorkPtr(int);
extern #ifdef NONMATCHING
/* Parked: 48 words differ (scheduling of the geometry/position copies around the D_0017B8C8 reloads). */
void nico_calcWormGenealogicalNodeHeadBase(void *);
extern void func_001289B8(void *, void *, void *);

void nico_calcWormGenealogicalNodeHead(HeadCtrl *ctrl)
{
    char *w = (char *)(((int)GetSCRCharaAIWorkPtr(ctrl->chara) + 0x41B3) & ~0xF);

    if (*(char *)(w + 0x1298) != 0) {
        nico_calcWormGenealogicalNodeHeadBase(ctrl);
        func_001289B8(w + 0x12A0, w + 0x60, B_001A5B50);
    } else {
        D_0017B8C8 = 0;
        *(s128 *)(w + 0x10) = *(s128 *)(ctrl->geo + ctrl->index * 0x40 + 0x30);
        *(s128 *)(w + D_0017B8C8 * 0x10 + 0xA20) = *(s128 *)(ctrl->pos + ctrl->index * 0x10);
    }
    if (*(char *)(w + 0x129B) != 0) {
        char *p = w + 0xF00;
        char *t0 = w + D_0017B8C8;
        char *rec = w + D_0017B8C8 * 0x50;
        int n = 0x1F;

        *(s128 *)(rec + 0x20) = ZeroVector;
        *(s128 *)(w + D_0017B8C8 * 0x10 + 0xC20) = *(s128 *)(rec + 0x10);
        *(char *)(t0 + 0xEA0) = 0;
        *(char *)(t0 + 0xEC0) = 0;
        *(char *)(t0 + 0xEE0) = 0;
        do {
            n--;
            *(int *)(p + 8) = 0;
            *(int *)(p + 0xC) = 0;
            *(int *)(p + 0x10) = 0;
            *(int *)(p + 0x14) = 0;
            p += 0x1C;
        } while (n >= 0);
        *(char *)(w + 0x1299) = 0;
    }
    D_0017B8C8 += 1;
}
#else
void nico_calcWormGenealogicalNodeHead(HeadCtrl *ctrl);
#endif
