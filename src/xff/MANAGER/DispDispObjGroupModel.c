typedef long long s64;
typedef unsigned long long u64;
typedef int s128 __attribute__((mode(TI)));
typedef struct { float x, y, z, w; } __attribute__((aligned(16))) V4;
typedef struct {
    char pad0[0x260];
    u64 bits;
} DispFlags;
typedef struct {
    char pad0[4];
    float depth;
    char pad8[0x18];
    float dist;
    char pad24[0xC];
    float lim;
    char pad34[0x9C];
    void (*draw)(int, int);
    void (*predraw)(int, int, int);
    void (*update)(int);
    int (*check)(int);
    char padE0[4];
    int arg;
} GeoDisp;
typedef struct {
    char pad0[0x40];
    V4 pos;
    char pad50[0x30];
    V4 rot;
    char pad90[0xA4];
    V4 *wpos;
    char pad138[4];
    V4 *quat;
    GeoDisp *geo;
    DispFlags *flags;
    char pad148[0x10];
    void *mtx;
    char pad15C[0x5A];
    char upd;
    char updPos;
    char dispUpd;
} LayoutClass;
typedef struct {
    char pad0[0xCC0];
    void (*setVisible)(int, int);
} CharacterClass;

extern int D_00136BE8;
extern int D_00136BF0;
extern int D_00136BF8;
extern int D_00136BFC;
extern int GetLayoutDispObjGroup(void);
extern void isysObjWaitSema(void);
extern void isysObjSignalSema(void);
extern void graphFsEffectReset(void);
extern void ClearSortList(int);
extern void AddSortObj(int, void *);
extern int *GetFirstSortObj(int);
extern int *GetNextSortObj(int, int *);
extern int *isysGroupForFirst(int, int);
extern int *isysGroupForNext(int *, int);
extern void isysGroupForExit(int, int);
extern LayoutClass *GetLayoutClass(int);
extern GeoDisp *GetGeoDispClass(int);
extern CharacterClass *GetCharacterClass(int);
extern void GetQuaternionByAxisDirZY(V4 *, V4 *, V4 *);
extern void UpdateLayoutClassSimpleGeometry(LayoutClass *, float);
extern void modelSetEnviroment(void);
extern void func_00079D28(int, int, int);
extern void iosDlLockObj(int);

static inline void localDirZ(V4 *out, V4 *q)
{
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmul.xyzw vf5, vf4, vf4\n"
                         "vmr32.xyzw vf6, vf4\n"
                         "vmul.xyzw vf7, vf6, vf4\n"
                         "vmr32.xyzw vf6, vf6\n"
                         "vmul.xyzw vf8, vf6, vf4\n"
                         "vsubx.z vf6, vf0, vf5x\n"
                         "vsuby.z vf6, vf6, vf5y\n"
                         "vaddw.y vf6, vf7, vf7w\n"
                         "vsuby.x vf6, vf8, vf8y\n"
                         "vsub.w vf6, vf0, vf0\n"
                         "vadd.w vf5, vf0, vf0\n"
                         "vmulw.xyz vf6, vf6, vf5w\n"
                         "vaddw.z vf6, vf6, vf0w\n"
                         "sqc2 vf6, 0x0(%0)\n"
                         : : "r"(out), "r"(q) : "memory");
}

static inline void localDirY(V4 *out, V4 *q)
{
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmul.xyzw vf5, vf4, vf4\n"
                         "vmr32.xyzw vf6, vf4\n"
                         "vmul.xyzw vf7, vf6, vf4\n"
                         "vaddy.z vf6, vf0, vf7y\n"
                         "vsubw.z vf6, vf6, vf7w\n"
                         "vsubx.y vf6, vf0, vf5x\n"
                         "vsubz.y vf6, vf6, vf5z\n"
                         "vaddz.x vf6, vf7, vf7z\n"
                         "vsub.w vf6, vf0, vf0\n"
                         "vadd.w vf5, vf0, vf0\n"
                         "vmulw.xyz vf6, vf6, vf5w\n"
                         "vaddw.y vf6, vf6, vf0w\n"
                         "sqc2 vf6, 0x0(%0)\n"
                         : : "r"(out), "r"(q) : "memory");
}

static inline void mulQuat(V4 *out, V4 *a, V4 *b)
{
    __asm__ __volatile__("lqc2 vf11, 0x0(%1)\n"
                         "lqc2 vf12, 0x0(%2)\n"
                         "vmul.xyzw vf13, vf11, vf12\n"
                         "vaddy.x vf13, vf13, vf13y\n"
                         "vaddz.x vf13, vf13, vf13z\n"
                         "vsubx.w vf13, vf13, vf13x\n"
                         "vmulw.xyz vf14, vf12, vf11w\n"
                         "vmulw.xyz vf15, vf11, vf12w\n"
                         "vopmula.xyz ACC, vf12, vf11\n"
                         "vopmsub.xyz vf16, vf11, vf12\n"
                         "vadd.xyz vf13, vf14, vf15\n"
                         "vadd.xyz vf13, vf13, vf16\n"
                         "sqc2 vf13, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void applyMatrix(V4 *out, void *mat, V4 *in)
{
    __asm__ __volatile__("lqc2 vf8, 0x0(%2)\n"
                         "lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x10(%1)\n"
                         "lqc2 vf16, 0x20(%1)\n"
                         "lqc2 vf17, 0x30(%1)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(out), "r"(mat), "r"(in) : "memory");
}

void DispDispObjGroupModel(int ctx)
{
    V4 dirY;
    V4 dirZ;
    int group;
    int obj;
    int *it;

    group = GetLayoutDispObjGroup();
    if (!D_00136BF0) {
        return;
    }
    isysObjWaitSema();
    obj = 0;
    graphFsEffectReset();
    ClearSortList(D_00136BF8);
    for (it = isysGroupForFirst(group, 0); it != 0; it = isysGroupForNext(it, 0)) {
        LayoutClass *lc;
        obj = *it;
        lc = GetLayoutClass(obj);
        if (lc != 0) {
            int hidden, vis, upd;
            GeoDisp *geo;
            LayoutClass *parent;

            hidden = 1;
            parent = GetLayoutClass(ctx);
            geo = lc->geo;
            vis = 1;
            upd = 0;
            if (lc->upd) {
                localDirZ(&dirZ, parent->quat);
                localDirY(&dirY, parent->quat);
                GetQuaternionByAxisDirZY(lc->quat, &dirZ, &dirY);
                mulQuat(lc->quat, lc->quat, &lc->rot);
                upd = 1;
            }
            if (lc->updPos) {
                applyMatrix(lc->wpos, parent->mtx, &lc->pos);
                mulQuat(lc->quat, parent->quat, &lc->rot);
                upd = 1;
            }
            if (upd) {
                UpdateLayoutClassSimpleGeometry(lc, 0.0f);
            }
            if (lc->dispUpd) {
                if (geo->update) {
                    geo->update(obj);
                }
                if (geo->check) {
                    vis = geo->check(obj);
                }
                if (geo->dist > 0.0f && geo->lim >= 0.0f) {
                    hidden = vis == 0;
                }
            }
            if (hidden != ((unsigned short)(lc->flags->bits >> 8) & 1)) {
                CharacterClass *ch = GetCharacterClass(obj);
                if (ch != 0 && ch->setVisible) {
                    ch->setVisible(obj, hidden);
                }
            }
            if (!hidden) {
                geo->depth = geo->dist;
                AddSortObj(D_00136BF8, geo);
            }
            lc->flags->bits = (lc->flags->bits & ~0x100) | ((u64)hidden << 8);
        } else {
            GeoDisp *geo = GetGeoDispClass(obj);
            if (geo->update) {
                geo->update(obj);
            }
            if (geo->dist > 0.0f && geo->lim >= 0.0f) {
                geo->depth = geo->dist;
                AddSortObj(D_00136BF8, geo);
            }
        }
    }
    if (obj) {
        isysGroupForExit(obj, 0);
    }
    ClearSortList(D_00136BFC);
    {
        int *s = GetFirstSortObj(D_00136BF8);
        while (s) {
            int *next = GetNextSortObj(D_00136BF8, s);
            LayoutClass *lc = GetLayoutClass(*s);
            if (lc != 0) {
                if (!(lc->flags->bits & 0x10)) {
                    AddSortObj(D_00136BFC, s);
                }
            } else {
                AddSortObj(D_00136BFC, s);
            }
            s = next;
        }
    }
    if (GetFirstSortObj(D_00136BFC)) {
        int list;
        int *s;
        modelSetEnviroment();
        func_00079D28(D_00136BFC, ctx, group);
        list = D_00136BFC;
        for (s = GetFirstSortObj(list); s != 0; s = GetNextSortObj(list, s)) {
            int o = *s;
            LayoutClass *lc = GetLayoutClass(o);
            if (lc != 0) {
                GeoDisp *geo = lc->geo;
                if (o) {
                    iosDlLockObj(o);
                }
                if (geo->predraw) {
                    geo->predraw(ctx, o, geo->arg);
                }
                geo->draw(ctx, o);
            } else {
                GeoDisp *geo = GetGeoDispClass(o);
                if (o) {
                    iosDlLockObj(o);
                }
                geo->draw(ctx, o);
            }
        }
    }
    isysObjSignalSema();
    D_00136BE8 = 0;
}
