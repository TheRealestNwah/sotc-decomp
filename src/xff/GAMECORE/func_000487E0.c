/* Parked: 79 diffs, same size (167 words). Ribbon strip draw: camera-inverse matrix (VU0 transpose block) loaded with glLoadMatrixf, additive-blend setup, then a triangle strip over points start..count with per-point alpha, two vertices and tex coords each (0x30 per point). Remaining: the Original keeps v + i*0x30 recomputed per iteration (no hoisted induction register), ours strength-reduces it, which shifts the saved registers and the tail. */
#ifdef NONMATCHING
extern char *iosgluGetCameraContext(void);
extern void iosDlPushLayer(int);
extern void iosDlPopLayer(void);
extern void *texSearchMopByName(char *);
extern void texTransRequest(void *, int, int);
extern void glEnable(int);
extern void glDisable(int);
extern void glBegin(int);
extern void glEnd(void);
extern char *iosGetCurrentDC(void);
extern void glSetReg(int, long);
extern void glBlendFunc(int, int);
extern void glZOffset(float);
extern void glLoadMatrixf(void *);
extern void glNormal3f(float, float, float);
extern void glColor4f(float, float, float, float);
extern void glTexCoord2f(float, float);
extern void glVertex4fv(void *);

static char s_boss_worm[] = "boss_worm";

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

static void func_000487E0(char *o, char *v)
{
    float m[16] __attribute__((aligned(16)));
    int s;
    int n;
    int i;
    int k;
    float *al;
    char *p;
    float *t;

    s = 0;
    n = *(int *)(o + 0x340);
    if (n > 0)
        s = n - 1;
    if (n < *(int *)(o + 0x98)) {
        al = *(float **)(*(char **)(o + 4) + 0x44);
        matInverse(m, (float *)(iosgluGetCameraContext() + 0x1A0));
        iosDlPushLayer(0x17);
        i = s;
        texTransRequest(texSearchMopByName(s_boss_worm), 0, 0);
        glEnable(3);
        glBegin(8);
        glSetReg(0x4E, *(int *)(iosGetCurrentDC() + 0x164) | 0x31000000 | 0x100000000L);
        glBlendFunc(5, 6);
        glDisable(4);
        glEnd();
        glZOffset(1.0f);
        glDisable(8);
        glEnable(7);
        glEnable(0);
        glLoadMatrixf(m);
        glBegin(5);
        glNormal3f(0.0f, 0.0f, 1.0f);
        if (!(*(int *)(o + 0x98) < i)) {
            al += i;
            do {
                glColor4f(1.0f, 1.0f, 1.0f, *al);
                p = (char *)((float *)v + i * 12);
                t = (float *)(p + 0x24);
                k = 1;
                do {
                    k--;
                    glTexCoord2f(t[-1], t[0]);
                    t += 2;
                    glVertex4fv(p);
                    p += 0x10;
                } while (k >= 0);
                i++;
                al++;
            } while (!(*(int *)(o + 0x98) < i));
        }
        glEnd();
        glDisable(0);
        glBegin(8);
        glSetReg(0x4E, *(int *)(iosGetCurrentDC() + 0x164) | 0x31000000);
        glBlendFunc(5, 6);
        glEnd();
        iosDlPopLayer();
    }
}
#endif
