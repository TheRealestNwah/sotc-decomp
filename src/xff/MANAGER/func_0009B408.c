#ifdef NONMATCHING /* parked draft: 156 diffs, VU0 runs in place (roughly wired) */
extern void EntryModifiedManager(void *, int);

void func_0009B408(char *obj, int idx)
{
    char *cls = (char *)(obj + 0x154);
    char *grp = *(char **)(*(char **)(obj + 0x184) + 0x20);
    char *m0 = *(char **)(grp + 0x18) + idx * 64;
    char *base = *(char **)(cls + 8);
    char *ent = *(char **)(cls + 0x20) + 0x28;
    char *ent0 = *(char **)(*(char **)(cls + 0x20) + 0x24);
    char *tab = *(char **)(grp + 8);
    char *recs = *(char **)(grp + 0x14);
    int a = *(int *)m0;
    int b = *(int *)(m0 + 4);
    char *dst;
    char *e;
    float *srcv;
    float *mt;
    char *rec;
    int *lp;
    int n;
    char *s;
    int a2, b2;

    if (a != -1) {
        e = ent0 + a * 96;
        rec = *(char **)(e + 0x14);
        dst = rec + b * 16;
        if (*(unsigned char *)(*(int *)(e + 8) + b) == 0) {
            srcv = (float *)(*(char **)(tab + a * 144 + 4) + b * 16);
            mt = (float *)(base + a * 64);
        __asm__ __volatile__("lqc2 vf8, 0x0(%0)\n"
                         "lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x10(%1)\n"
                         "lqc2 vf16, 0x20(%1)\n"
                         "lqc2 vf17, 0x30(%1)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0x0(%2)\n"
                             : : "r"(srcv), "r"(mt), "r"(rec) : "memory");
            EntryModifiedManager(e, b);
        }
    } else {
        dst = *(char **)(ent + 0x14) + b * 16;
        if (*(unsigned char *)(*(int *)(ent + 8) + b) == 0) {
            lp = (int *)(*(int *)(recs + b * 4));
            s = (char *)(lp + 1);
            a2 = *(int *)s;
            b2 = *(int *)(s + 4);
            e = ent0 + a2 * 96;
            rec = *(char **)(e + 0x14) + b2 * 16;
            if (*(unsigned char *)(*(int *)(e + 8) + b2) == 0) {
                srcv = (float *)(*(char **)(tab + a2 * 144 + 4) + b2 * 16);
                mt = (float *)(base + a2 * 64);
        __asm__ __volatile__("lqc2 vf8, 0x0(%0)\n"
                         "lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x10(%1)\n"
                         "lqc2 vf16, 0x20(%1)\n"
                         "lqc2 vf17, 0x30(%1)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0x0(%2)\n"
                             : : "r"(srcv), "r"(mt), "r"(rec) : "memory");
                EntryModifiedManager(e, b2);
            }
        __asm__ __volatile__("lqc2 vf31, 0x0(%0)\n"
                             : : "r"(rec) : "memory");
            n = *lp - 2;
            s += 8;
            while (n != -1) {
                a2 = *(int *)s;
                b2 = *(int *)(s + 4);
                e = ent0 + a2 * 96;
                rec = *(char **)(e + 0x14) + b2 * 16;
                if (*(unsigned char *)(*(int *)(e + 8) + b2) == 0) {
                    srcv = (float *)(*(char **)(tab + a2 * 144 + 4) + b2 * 16);
                    mt = (float *)(base + a2 * 64);
        __asm__ __volatile__("lqc2 vf8, 0x0(%0)\n"
                         "lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x10(%1)\n"
                         "lqc2 vf16, 0x20(%1)\n"
                         "lqc2 vf17, 0x30(%1)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0x0(%2)\n"
                             : : "r"(srcv), "r"(mt), "r"(rec) : "memory");
                    EntryModifiedManager(e, b2);
                }
        __asm__ __volatile__("lqc2 vf30, 0x0(%0)\n"
                         "vadd.xyzw vf31, vf29, vf30\n"
                             : : "r"(rec) : "memory");
                n--;
                s += 8;
            }
        __asm__ __volatile__("sqc2 vf31, 0x0(%0)\n"
                             : : "r"(dst) : "memory");
        }
    }
    EntryModifiedManager(ent, b);
}
#endif
