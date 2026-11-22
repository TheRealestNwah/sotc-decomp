typedef unsigned int qword __attribute__((mode(TI)));
extern int DldSysUndefSymbol;
typedef struct { char pad0[0xC]; int size; } DldType;
typedef struct { char pad0[8]; DldType *type; char padC[4]; char *data; } DldTable;
typedef struct { char *res; int pad4; float frame; } OptNode;
extern int GetMotionVersion(void *);
extern int GetMotionNbOptionNodes(void *);
extern int GetMotionOptionNodePhysicalId(void *, int);
extern void GetMotionOptionNodeIntFrame(void *, void *, void *, void *, int, int);
extern void GetMotionOptionNodeFloatFrame(void *, void *, void *, void *, int, float);

static inline void *dldElement(int *h)
{
    int off = *h & 0x3FFFF;
    DldTable *t = off != 0 ? *(DldTable **)((char *)h - off) : 0;
    return (t != 0 && t != (DldTable *)DldSysUndefSymbol) ? t->data + (((unsigned int)*h >> 18) & 0xFFF) * t->type->size : 0;
}

static inline int physId(int *options, void *motion, int node)
{
    int result = -1;
    if (*options <= 0 || GetMotionVersion(motion) < 5) {
        if (node < GetMotionNbOptionNodes(motion))
            result = node;
    } else {
        result = GetMotionOptionNodePhysicalId(motion, node);
    }
    return result;
}

static inline void quatMul(qword *out, qword *a, qword *b)
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

static inline void vecAdd(qword *out, qword *a, qword *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)
"
                         "lqc2 vf6, 0x0(%2)
"
                         "vadd.xyz vf5, vf5, vf6
"
                         "sqc2 vf5, 0x0(%0)
"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void vecSub(qword *out, qword *a, qword *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)
"
                         "lqc2 vf6, 0x0(%2)
"
                         "vsub.xyz vf5, vf5, vf6
"
                         "sqc2 vf5, 0x0(%0)
"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

void AddCharacterClassOptionNodeSubGeometry(qword *rot, qword *pos, char *chr, OptNode *node, int index)
{
    qword v[5];
    char *res = node->res;
    if (res != 0) {
        int *options = *(int **)(chr + 0x358);
        char *motion = res + 0x50;
        int id = physId(options, motion, index);
        char *e;
        qword *iq, *fv, *iv, *w;
        if (id < 0)
            return;
        e = dldElement((int *)(res + 0x28));
        if (e != 0) {
            char *m2 = e + 0x50;
            int id2 = physId(options, m2, index);
            if (id2 < 0)
                return;
            iq = &v[1];
            iv = &v[3];
            w = &v[4];
            GetMotionOptionNodeIntFrame(iq, iv, w, m2, id2, 0);
        } else {
            iq = &v[1];
            iv = &v[3];
            w = &v[4];
            GetMotionOptionNodeIntFrame(iq, iv, w, motion, id, 0);
        }
        fv = &v[2];
        GetMotionOptionNodeFloatFrame(&v[0], fv, w, motion, id, node->frame);
        vecSub(fv, fv, iv);
        __asm__ __volatile__("lqc2 vf11, 0x0(%0)
"
                             "vsubw.x vf5, vf0, vf0w
"
                             "vmulx.xyz vf11, vf11, vf5x
"
                             "sqc2 vf11, 0x0(%0)
"
                             : : "r"(iq) : "memory");
        quatMul(rot, rot, iq);
        vecAdd(pos, pos, fv);
        quatMul(rot, rot, &v[0]);
    }
}
