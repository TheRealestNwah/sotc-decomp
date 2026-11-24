/* Parked: 9 diffs, same size. Per-frame update of the slow-leg move controller: builds a base-move work block on the stack, turns the character quaternion into a matrix and its inverse, steers by direct input, then either keeps the passage target, clears it (no target), or checks whether the layout target is reached; when not reached it re-checks from the work position with the layout block temporarily swapped, picks the motion with func_0010E5A8 and applies scale. Remaining: the quaternion pointer and matrix output take v0/v1 swapped. The x1C4 store goes through a union with long so it aliases the layout block's ld/sd copy and stays before the restore. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));

typedef struct {
    int x[4];
    char *q[4];
} __attribute__((aligned(8))) Blk;

typedef struct {
    char pad0[0xC];
    s128 *target;
    int x10;
    char *chr;
    int x18;
    char pad1C[4];
    float mat[4][4] __attribute__((aligned(16)));
    float inv[4][4] __attribute__((aligned(16)));
    char padA0[4];
    float a4;
    char padA8[0xCC - 0xA8];
    void *owner;
    char padD0[0x158 - 0xD0];
    float x158;
    float x15C;
    float x160;
    char pad164[0x190 - 0x164];
    s128 pos;
    Blk blk;
    int x1C0;
    float x1C4;
    char pad1C8[0x1D8 - 0x1C8];
    int x1D8;
    char pad1DC[0x1F0 - 0x1DC];
} Tmp;

typedef struct {
    char pad0[4];
    int x4;
    char pad8[8];
    s128 x10;
    int x20;
    char pad24[0x40 - 0x24];
    float x40;
} Ctrl;

typedef struct {
    char pad0[0xA8];
    int xA8;
    char padAC[0xE0 - 0xAC];
    int xE0;
    float xE4;
    char padE8[0x3E0 - 0xE8];
    Blk blk;
} Lay;

extern s128 fltMaxVector;
extern void _initBaseMoveTmpWork(void *, Tmp *, Ctrl *, Lay *);
extern void iosInverseMatrix(void *, void *);
extern void func_0010DF90(Tmp *);
extern void SCRCharaTurnDirectInput(void *, float);
extern int _compPassagePos(Tmp *);
extern void func_0010FA88(Ctrl *);
extern void func_0010FA90(Tmp *, s128 *, int);
extern int func_0010E5A8(Tmp *, int, int);
extern void func_0010F110(Tmp *, int, float);
extern void func_0010F710(Tmp *, int);
extern void func_0010F338(Tmp *);
extern int setLockPassageWork(Lay *, int);
extern int chkAttainExecLayout(Lay *, s128 *, int, char *);
extern void _setAttainFlagBaseMoveWork(Ctrl *, int);

static inline void quatToMatrix(float *out, float *quat)
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
                         : : "r"(out), "r"(quat));
}

static inline void unitRow(float *out)
{
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"(out));
}

static inline void matInverse(float *dst, float *src)
{
    __asm__ __volatile__("lqc2 vf24, 0x30(%1)\n"
                         "vsubw.x vf25, vf0, vf0w\n"
                         "vmulx.xyz vf28, vf24, vf25x\n"
                         "vsub.w vf28, vf28, vf28\n"
                         "lq $8, 0x0(%1)\n"
                         "lq $9, 0x10(%1)\n"
                         "lq $10, 0x20(%1)\n"
                         "qmfc2.ni $11, vf0\n"
                         "pextlw $12, $9, $8\n"
                         "pextuw $13, $9, $8\n"
                         "pextlw $14, $11, $10\n"
                         "pextuw $15, $11, $10\n"
                         "pcpyld $8, $14, $12\n"
                         "pcpyud $9, $12, $14\n"
                         "pcpyld $10, $15, $13\n"
                         "pcpyud $11, $13, $15\n"
                         "qmtc2.ni $8, vf24\n"
                         "qmtc2.ni $9, vf25\n"
                         "qmtc2.ni $10, vf26\n"
                         "vmulax.xyzw ACC, vf24, vf28x\n"
                         "vmadday.xyzw ACC, vf25, vf28y\n"
                         "vmaddaz.xyzw ACC, vf26, vf28z\n"
                         "vmaddw.xyzw vf29, vf0, vf28w\n"
                         "vsub.w vf29, vf29, vf29\n"
                         "vadd.w vf29, vf29, vf0\n"
                         "sqc2 vf24, 0x0(%0)\n"
                         "sqc2 vf25, 0x10(%0)\n"
                         "sqc2 vf26, 0x20(%0)\n"
                         "sqc2 vf29, 0x30(%0)\n"
                         : : "r"(dst), "r"(src) : "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "memory");
}

void updateSlowLegCtrlWork(void *th, Ctrl *ctrl, Lay *lay, int arg3)
{
    Tmp w;
    Tmp *p = &w;
    Tmp *b = &w;
    Blk save;
    int r;

    _initBaseMoveTmpWork(th, p, ctrl, lay);
    p->x1D8 = arg3;
    p->owner = ctrl;
    {
        float *m = w.mat[0];
        quatToMatrix(m, (float *)(w.chr + 0x470));
        m += 12;
        unitRow(m);
    }
    matInverse(b->mat[0], b->mat[0]);
    iosInverseMatrix(b->inv, b->mat);
    func_0010DF90(p);
    SCRCharaTurnDirectInput(th, 0.0f);
    if (_compPassagePos(p) != 0) {
        ctrl->x10 = *b->target;
        func_0010FA88(ctrl);
    }
    if (ctrl->x4 == 0) {
        ctrl->x10 = fltMaxVector;
        func_0010FA88(ctrl);
        p->x160 = ctrl->x40;
        ctrl->x40 = 1.0f;
    } else if (b->target != 0) {
        if (b->x10 != 0) {
            func_0010FA90(p, &p->pos, 0);
            {
                int m = func_0010E5A8(p, 0, 0);
                if (0.0f < b->a4)
                    func_0010F110(p, m, p->x158);
                func_0010F710(p, m);
            }
        } else {
            Blk *bp;
            func_0010FA90(p, &p->pos, 0);
            setLockPassageWork(lay, 1);
            bp = &lay->blk;
            r = chkAttainExecLayout(lay, b->target, b->x18, b->chr);
            if (*(int *)(b->chr + 0x750) == ctrl->x20 && b->a4 == 0.0f && r == 1
                && (lay->xA8 == 0 || lay->xE0 != 0 || __builtin_fabsf(p->x15C) < lay->xE4)) {
                setLockPassageWork(lay, 0);
                _setAttainFlagBaseMoveWork(ctrl, 1);
            } else {
                if (p->x1C0 != 0) {
                    save = *bp;
                    *bp = p->blk;
                    r = chkAttainExecLayout(lay, &p->pos, b->x18, b->chr);
                    ((union { float f; long l; } *)&p->x1C4)->f = *(float *)((char *)bp + 0x14);
                    *bp = save;
                } else {
                    p->x1C4 = *(float *)((char *)bp + 0x14);
                }
                {
                    int m = func_0010E5A8(p, 1, r);
                    func_0010F710(p, m);
                    if (0.0f < b->a4)
                        func_0010F110(p, m, p->x158);
                }
            }
        }
    } else {
        p->x160 = 1.0f;
    }
    func_0010F338(p);
}
#endif
