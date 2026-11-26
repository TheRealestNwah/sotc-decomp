/* Parked: 21 diffs. Synchronised motion: resets the damage class, and if the layout has a sync
   list, takes the parent node's quaternion matrix and runs func_0008D6D0 for each active entry
   at the current float frame. The node++/node-- pair (from the permuter) gets the Original's
   register split for node and parent; an empty asm after the fr[2] store keeps it ahead of the
   count load like the Original (23 before). Remaining: loop counter, id and entry pointer use
   s0/s1/s2 in a different order, node and the kinds offset swap between s7 and fp, and the
   i = 0 / node = 0 moves are scheduled differently. */
#ifdef NONMATCHING
extern int GetDamageClass(void *);
extern void ResetDamageClass(int);
extern void CheckLetter(void *, void *);
extern int CheckDamageLetter;
extern char *GetGeometryPointerObject(void *);
extern int GetGeometryPointerObjectParentNodeId(void *);
extern char *GetAnimationClass(void *);
extern char *GetCharacterClass(void *);
extern void GetMotionNodeQuaternionPos(void *, void *, void *, int, int);
extern int GetObjectAnimationParentNodeId(int, int);
extern int GetObjectAnimationFloatFrame(void *, int, int, float, float);
extern void func_0008D6D0(void *, int, void *, void *, int, void *, int, int *, int, float, float);

static inline void quatMatrix(void *dst, void *q, void *t)
{
    __asm__ __volatile__("vaddw.xyz vf12, vf0, vf0w\n"
                         "lqc2 vf11, 0x0(%1)\n"
                         "vmr32.w vf14, vf0\n"
                         "vmr32.w vf15, vf0\n"
                         "vmr32.w vf16, vf0\n"
                         "vopmula.xyz ACC, vf11, vf12\n"
                         "vmadd.xyz vf11, vf0, vf0\n"
                         "vmadd.xyz vf10, vf11, vf12\n"
                         "vmul.xyz vf13, vf11, vf10\n"
                         "vopmula.xyz ACC, vf11, vf10\n"
                         "vmaddw.xyz vf15, vf10, vf11w\n"
                         "vmsubw.xyz vf16, vf10, vf11w\n"
                         "vopmula.xyz ACC, vf13, vf12\n"
                         "vmadd.xyz vf17, vf13, vf12\n"
                         "vopmula.xyz ACC, vf15, vf12\n"
                         "vmadd.xyz vf15, vf0, vf0\n"
                         "vsub.xyz vf14, vf12, vf17\n"
                         "vmove.yz vf17, vf14\n"
                         "vmove.y vf14, vf16\n"
                         "vmove.y vf16, vf15\n"
                         "vmove.y vf15, vf17\n"
                         "vmove.z vf14, vf15\n"
                         "vmove.z vf15, vf16\n"
                         "vmove.z vf16, vf17\n"
                         "sqc2 vf14, 0x0(%0)\n"
                         "sqc2 vf15, 0x10(%0)\n"
                         "sqc2 vf16, 0x20(%0)\n"
                         : : "r"(dst), "r"(q) : "memory");
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmove.w vf4, vf0\n"
                         "sqc2 vf4, 0x30(%0)\n"
                         : : "r"(dst), "r"(t) : "memory");
}

typedef struct { int n; int pad[5]; int *kinds; } AnimHdr;
typedef struct { int id; int arg; } AnimEnt;

int ExecMotionSyncAnimation(char *obj, int arg1, float t, float dt)
{
    char buf[0x60];
    char *cls;
    char *lay;
    float *fr;
    AnimHdr *h;
    int anim;

    if (t == 0.0f)
        return 0;
    ResetDamageClass(GetDamageClass(obj));
    CheckLetter(obj, &CheckDamageLetter);
    cls = (unsigned char)obj[8] == 0xD ? obj + 0x20 : 0;
    lay = cls + 0x70;
    fr = (float *)(cls + 0x2E0);
    h = *(AnimHdr **)(cls + 0x328);
    anim = *(int *)(cls + 0x334);
    if (*(int *)(lay + 0x124) != 0) {
        char *geom = GetGeometryPointerObject(cls + 0x130);
        int nodeId = GetGeometryPointerObjectParentNodeId(cls + 0x130);
        int ci = *(int *)(cls + 0x350);
        char *ac;
        void *parent;
        int node;
        int cnt;
        int i;
        AnimEnt *e;

        if (ci < 0)
            ac = GetAnimationClass(geom);
        else
            ac = *(char **)(GetCharacterClass(geom) + 0x30C) + ci * 0x80 + 4;
        node = -1;
        parent = 0;
        if (nodeId > 0) {
            GetMotionNodeQuaternionPos(*(void **)(lay + 0x13C), *(void **)(lay + 0x134), geom, nodeId, 1);
            quatMatrix(*(void **)(lay + 0x158), *(void **)(lay + 0x13C), *(void **)(lay + 0x134));
            parent = obj;
            node = 0;
        }
        fr[2] = *(float *)(ac + 8);
        __asm__ volatile("");
        cnt = h->n;
        e = *(AnimEnt **)(cls + 0x338);
        i = 0;
        node++;
        node--;
        while (cnt--) {
            int id = e->id;
            if (id != 0) {
                if (nodeId < 0) {
                    node = GetObjectAnimationParentNodeId(anim, i);
                    parent = geom;
                }
                GetObjectAnimationFloatFrame(buf, anim, i, fr[2], fr[3]);
                func_0008D6D0(cls, id, geom, parent, node, buf, arg1, h->kinds + i * 3, e->arg, t, dt);
            }
            i++;
            e++;
        }
        fr[3] = fr[2];
    }
    return 0;
}
#endif
