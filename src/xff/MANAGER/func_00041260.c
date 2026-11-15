#ifdef NONMATCHING /* 112 diffs: word count matches (136); stack slot order (buf 0, count 0x10, v90 0x14) and saved-register numbering differ */
typedef int s128 __attribute__((mode(TI)));

extern char All1Vector[];
extern int GetOptionNodePhysicalNodeId(void *, void *, int);
extern void GetMotionOptionNodeFloatFrame(void *, void *, void *, void *, int, float);
extern void AddCharacterClassOptionNodeSubGeometries(void *, void *, void *, int);
extern void AddCharacterClassOptionNodeSubGeometry(void *, void *, void *, void *, int);
extern int GetMotionVersion(void *);
extern int GetMotionOptionNodePhysicalId(void *, int);
extern void GetMotionOptionNodeBooleanInfoFloatFrame(void *, void *, int, float, float);

void func_00041260(char *c)
{
    volatile char *v90;
    volatile int count = 0;
    s128 buf;
    char *bp;
    int a1;
    char *opt = *(char **)(c + 0x358);
    int i = 0;
    char *s2;
    char *s5;
    char *s4;
    char *s6;
    char *s0;
    char *s3;
    int id;
    int flag;

    if (opt)
        count = *(int *)(opt + 0x20);
    s2 = *(char **)(c + 0x2F0);
    s5 = *(char **)(c + 0x2EC);
    s4 = *(char **)(c + 0x2FC);
    if (count > 0) {
        v90 = c + 0x90;
        s6 = c + 0x1C0;
        goto first;
        for (;;) {
            opt = *(char **)(c + 0x358);
first:
            bp = (char *)&buf;
            s3 = *(char **)(opt + 0x24) + i * 64;
            s0 = *(char **)s6;
            id = -1;
            if (s0) {
                a1 = (int)s0 + 0x50;
                if (a1 != 0)
                    id = GetOptionNodePhysicalNodeId(opt, (void *)a1, i);
            }
            if (id >= 0) {
                GetMotionOptionNodeFloatFrame(s5, s2, bp, s0 + 0x50, id, *(float *)(s6 + 8));
                flag = *(char *)(c + 0x52E);
            } else {
                *(s128 *)s5 = *(s128 *)(s3 + 0x20);
                *(s128 *)s2 = *(s128 *)(s3 + 0x10);
                *(s128 *)bp = *(s128 *)All1Vector;
                flag = *(char *)(c + 0x52E);
            }
            if (flag) {
                AddCharacterClassOptionNodeSubGeometries(s5, s2, c, i);
                if (*(unsigned char *)(c + 0xD90) == 2) {
                    if (*(int *)(c + 0xD20) != 0 || *(float *)(c + 0x734) < 1.0f)
                        AddCharacterClassOptionNodeSubGeometry(s5, s2, c, c + 0xD20, i);
                }
            }
            __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                                 "lqc2 vf6, 0x0(%1)\n"
                                 "vmul.xyz vf5, vf5, vf6\n"
                                 "sqc2 vf5, 0x0(%0)\n"
                                 : : "r"(s2), "r"(v90) : "memory");
            s0 = 0;
            if (*(int *)s6)
                s0 = *(char **)s6 + 0x50;
            s4[2] = 0;
            s4[1] = 0;
            s4[0] = 0;
            if (s0) {
                if (*(int *)opt > 0) {
                    if (GetMotionVersion(s0) >= 5) {
                        int pid = GetMotionOptionNodePhysicalId(s0, i);
                        if (pid >= 0)
                            GetMotionOptionNodeBooleanInfoFloatFrame(s4, s0, pid, *(float *)(s6 + 8), *(float *)(s6 + 0xC));
                    }
                }
            }
            i++;
            s2 += 0x10;
            s5 += 0x10;
            s4 += 3;
            if (!(i < count))
                break;
        }
    }
}
#endif
