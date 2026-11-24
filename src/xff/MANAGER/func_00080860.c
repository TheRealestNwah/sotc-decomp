/* Creates the layout object, light or wind/part/cam animation for each sub-object of an LWS orient object and links it to the group. */
#ifdef NONMATCHING
/* Parked: 0 diffs, same size (281 words): try_compilers says MATCH, but the splice can't place its .rodata.
   func_0007F5A0 takes its floats after the fourth argument, which places the f13 move before t1 as in the
   Original. Remaining: in the Original the strings start at .rodata+0x4928, right after func_0007FD48's jump
   table (.rodata+0x4920), and this jump table sits at +0x4A30 (16-aligned relative to that object start).
   Alone, the C file puts the table 8 bytes too early. It needs func_0007FD48 (and GetLwsOrientWorkSize) in
   the same C file, and the function made static (Placeholder name). */
typedef struct { float x, y, z, w; } __attribute__((aligned(16))) Vec;
typedef int u_long128 __attribute__((mode(TI)));

typedef struct {
    int flag;
    int type;
    int param;
} SubDef;

typedef struct {
    int layout;
    int sub;
    char pad8[8];
    Vec s;
    Vec t;
    Vec r;
    Vec q;
} SubWork;

typedef struct {
    int pad0[7];
    int one;
    void *geo;
    int link;
    int pad28[3];
    int two;
    int pad38;
} LayoutParam;

extern int DldSysUndefSymbol;
extern char rootPtn[];
extern Vec ZeroPoint;
extern Vec IdentityQuaternion;
extern void SetGeometryPointerNodePosState(void *, void *, int, Vec *, Vec *);
extern char *getAnimObjResource(int);
extern char *GetLayoutClass(int);
extern int GetObjectAnimationFloatFrame(void *, void *, int, float, float);
extern int initLayoutObj(char *, void *, int, LayoutParam *);
extern void updateLayoutGeo(char *, void *, int, void *, float);
extern int StartAnimationSubObjInfinitePart(int, int, int, void *, int, int, void *, int);
extern int AddGaLightMan(int *, void *, int);
extern void ForceGameLightFlagEnvelope(int);
extern void func_0007F5A0(int, void *, void *, int, float, float, SubDef *, SubWork *, int, int);
extern int isysAddGroupWithLinkParam(int, int, int, int);
extern void GetTRS_Onake_From_ObjectAnimation(void *, Vec *, Vec *, Vec *, Vec *);

static inline int resolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return t != 0 && t != (int *)DldSysUndefSymbol ? t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

void func_00080860(void *obj, int *def, char *cls, void *tail, char *info, int *def2, char *cc, int n)
{
    char geo[0x40];
    char anim[0x60];
    LayoutParam param;
    int base;
    char *res;
    char *lc;
    SubDef *sd;
    SubWork *w;
    int i = 0;
    register int *dp __asm__("$23");

    SetGeometryPointerNodePosState(geo, obj, 0, &IdentityQuaternion, &ZeroPoint);
    dp = def;
    base = dp[31];
    res = getAnimObjResource(base + 0x50);
    lc = GetLayoutClass((int)obj);
    param.one = 1;
    param.link = def2[21];
    param.two = 2;
    /* Keeps the one/link/two stores in field order, like the Original. */
    __asm__ volatile("" : : "m"(param));
    param.pad0[0] = 0;
    param.pad0[1] = 0;
    param.pad0[2] = 0;
    param.pad0[3] = 0;
    param.geo = geo;
    param.pad0[4] = 0;
    param.pad0[5] = 0;
    param.pad0[6] = 0;
    param.pad28[0] = 0;
    param.pad28[1] = 0;
    param.pad28[2] = 0;
    param.pad38 = 0;
    {
        register u_long128 *src __asm__("$3") = *(u_long128 **)(lc + 0x134);
        register u_long128 *dst __asm__("$4") = *(u_long128 **)(cls + 0x11F8);
        register u_long128 t __asm__("$2");

        __asm__ volatile("lq %0, 0(%1)\n\tsq %0, 0(%2)" : "=&r"(t) : "r"(src), "r"(dst));
    }
    {
        u_long128 t;

        __asm__ volatile("lq %0, %1" : "=r"(t) : "m"(*(u_long128 *)(cc + 0x470)) : "memory");
        __asm__ volatile("sq %1, %0" : "=m"(*(u_long128 *)(*(char **)(cls + 0x11F8) + 0x20)) : "r"(t));
    }
    sd = *(SubDef **)(info + 0x54);
    w = *(SubWork **)(cls + 0x1200);
    if (n > 0) {
        for (; i < n; i++, w++, sd++) {
            int *ent;

            w->sub = 0;
            ent = (int *)(*(int *)(res + 0x10) + i * 12);
            GetObjectAnimationFloatFrame(anim, getAnimObjResource(dp[31] + 0x50), i, 0.0f, 0.0f);
            switch (sd->type = *ent) {
            case 1:
            case 5:
                if (sd->param != 0) {
                    w->layout = initLayoutObj("lwsori_subobj", rootPtn, sd->param, &param);
                    updateLayoutGeo(GetLayoutClass(w->layout), obj, 0, anim, 0.0f);
                }
                break;
            case 38:
                w->layout = initLayoutObj("lwsori_subobj_sprit", rootPtn, 0, &param);
                break;
            case 3:
                if (sd->param != 0) {
                    w->layout = initLayoutObj("lwsori_subobj_damage", rootPtn, 0, &param);
                }
                break;
            case 13:
                if (sd->param != 0) {
                    w->layout = initLayoutObj("lwsori_subobj_dam_box", rootPtn, 0, &param);
                }
                break;
            case 10:
                if (sd->param != 0) {
                    w->layout = initLayoutObj("lwsori_subobj_dam_cylinder", rootPtn, 0, &param);
                }
                break;
            case 9:
                if (sd->param != 0) {
                    w->layout = initLayoutObj("lwsori_subobj_lws_trigger", rootPtn, 0, &param);
                    *(u_long128 *)(GetLayoutClass(w->layout) + 0x90) = *(u_long128 *)(lc + 0x90);
                }
                break;
            case 6:
                if (sd->param != 0) {
                    w->layout = initLayoutObj("lwsori_subobj_light", rootPtn, 0, &param);
                }
                break;
            case 11:
                if (sd->param != 0) {
                    w->layout = initLayoutObj("lwsori_subobj_effect", rootPtn, 0, &param);
                }
                break;
            case 12:
                if (sd->param != 0) {
                    w->layout = initLayoutObj("lwsori_subobj_se", rootPtn, 0, &param);
                }
                break;
            case 2:
            case 4:
            case 7:
            case 39:
            case 40:
            case 41:
            case 42:
            case 45:
            case 47:
            case 48:
                if (sd->param != 0) {
                    int l = initLayoutObj("lwsori_subobj_wind/part/cam", rootPtn, 0, &param);

                    w->layout = l;
                    if (sd->flag != 0) {
                        w->sub = StartAnimationSubObjInfinitePart(0, l, 0, obj, 0, sd->type, anim, sd->param);
                    }
                }
                break;
            case 27:
            case 28:
            case 33:
            case 34:
            case 35: {
                int m = AddGaLightMan(ent, anim, sd->param);

                w->sub = m;
                if (*(int *)(lc + 0x124) != 0 && m != 0) {
                    ForceGameLightFlagEnvelope(m);
                }
                break;
            }
            }
            if (w->layout != 0) {
                func_0007F5A0(w->layout, obj, anim, 0, 1.0f, 1.0f, sd, w, resolve((unsigned int *)(base + 0xC8)),
                              *(int *)(cls + 0x11FC));
                isysAddGroupWithLinkParam(w->layout, dp[73], 0, 0);
                GetTRS_Onake_From_ObjectAnimation(anim, &w->s, &w->t, &w->r, &w->q);
            }
        }
    }
}
#else
extern void func_00080860(void *obj, int *def, char *cls, void *tail, char *info, int *def2, char *cc, int n);
#endif
