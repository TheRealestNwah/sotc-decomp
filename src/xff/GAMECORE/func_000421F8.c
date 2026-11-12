/* func_000421F8: scales the layout class by an animation frame. The VU0 operand order of the two asm blocks and GetTwoWayLinkData taking only the node fix the register allocation (the vec argument lives on the stack in the original). */
typedef int s128 __attribute__((mode(TI)));
extern char RO_0017D150[];
extern int GetTwoWayLinkNext(void *);
extern int GetTwoWayLinkData(int);
extern char *GetScriptAnimationClass(int);
extern char *GetLayoutClass(int);
extern int strcmp(const char *, const char *);
extern void GetObjectAnimationFloatFrame(void *, int, int, float, float);
extern void SetLayoutClassScaleElem(void *, void *, int);

static void func_000421F8(char *o, float *vec)
{
    struct { s128 tmp; s128 frame; char pad[0x20]; s128 anim; char pad2[0x20]; s128 res; } v;
    int node;
    char *cls;
    char *fp;
    int *list;
    int n;
    int i;

    node = GetTwoWayLinkNext(o + 0x10C);
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "lqc2 vf6, 0x0(%3)\n"
                         "vmul.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf5, 0x0(%4)\n"
                         "lqc2 vf6, 0x0(%1)\n"
                         "vmul.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%4)\n"
                         "lqc2 vf5, 0x0(%2)\n"
                         "lqc2 vf6, 0x0(%1)\n"
                         "vmul.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%2)\n"
                         :
                         : "r"(vec), "r"(&v.tmp), "r"(o + 0x4F0), "r"(o + 0xA0), "r"(o + 0x4E0)
                         : "memory");
    while (node != 0) {
        cls = GetScriptAnimationClass(GetTwoWayLinkData(node));
        if (cls != 0) {
            fp = o + 0x1C0;
            list = *(int **)(cls + 0x338);
            n = **(int **)(cls + 0x328);
            for (i = 0; --n != -1; i++) {
                int e = *list;

                list += 2;
                if (e != 0 && strcmp(*(char **)(GetLayoutClass(e) + 0x130), RO_0017D150) == 0) {
                    GetObjectAnimationFloatFrame(&v.frame, *(int *)(cls + 0x334), i, *(float *)(fp + 8), *(float *)(fp + 0xC));
                    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                                         "lqc2 vf6, 0x0(%2)\n"
                                         "vmul.xyz vf5, vf5, vf6\n"
                                         "sqc2 vf5, 0x0(%0)\n"
                                         :
                                         : "r"(&v.res), "r"(vec), "r"(&v.anim)
                                         : "memory");
                    SetLayoutClassScaleElem(o, &v.res, 1);
                    return;
                }
            }
        }
        node = GetTwoWayLinkNext((void *)node);
    }
    SetLayoutClassScaleElem(o, vec, 1);
}
