/* Parked: 2 words off; "last = 0" is scheduled before the argument setup instead of into the delay
   slot of the isysGroupForFirst call. "changed = 1" after the advance call keeps it in $v1, and an
   empty asm barrier keeps "last = 0" before the call. */
#ifdef NONMATCHING
typedef struct Orient {
    char pad0[4];
    float f4;
} Orient;

typedef struct Mgr {
    char pad0[0x20];
    int flag;       /* 0x20 */
    char pad24[0xC];
    char pad30[0x60];
} Mgr;

extern Orient *GetDemoOrientNext(void *);
extern void func_0007E2D0(void *, void *, void *, void *, float, int);
extern void isysDeleteGroupAllObj(void *);
extern void isysGroupForExit(int, int);
extern int *isysGroupForFirst(void *, int);
extern int *isysGroupForNext(int *, int);
extern void isysRequestDeleteObj(int);

void ExecLwsDemoOrientManagerObj(char *obj, float a, float dt)
{
    int changed = 0;
    char *g = obj + 0x20;
    char *list = obj + 0x90;
    Orient *cur;
    float t;

    t = *(float *)(g + 0x94) + dt;
    cur = *(Orient **)(list + 0x14);
    *(float *)(g + 0x94) = t;
    if (*(int *)(g + 0x90) != 0) {
        *(int *)(g + 0x90) = 0;
        if (cur != 0 && cur->f4 != -2.0f) {
            do {
                cur = GetDemoOrientNext(list);
            } while (cur != 0 && cur->f4 != -2.0f);
        }
        goto advance;
    }
    {
        float f1 = cur->f4;
        if (f1 > 0.0f && f1 < t) {
advance:
            cur = GetDemoOrientNext(list);
            changed = 1;
        }
    }
    {
        char *sub = g + 0x98;
        if (changed != 0) {
            int last = 0;
            int *e;
            __asm__ __volatile__("");
            e = isysGroupForFirst(sub, 0);
            if (e != 0) {
                do {
                    last = *e;
                    isysRequestDeleteObj(last);
                    e = isysGroupForNext(e, 0);
                } while (e != 0);
            }
            if (last != 0)
                isysGroupForExit(last, 0);
            isysDeleteGroupAllObj(sub);
            if (cur != 0) {
                func_0007E2D0(sub, cur, g + 0x70, obj, a, (cur->f4 < -2.0f) ? 5 : 4);
                *(float *)(g + 0x94) = 0.0f;
            }
        }
    }
}
#else
extern void ExecLwsDemoOrientManagerObj(char *, float, float);
#endif
