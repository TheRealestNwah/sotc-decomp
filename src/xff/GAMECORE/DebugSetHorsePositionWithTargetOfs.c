/* Parked: 53 diffs, 103 words vs 101 (96 for the straight draft). Horse reposition debug: VU0 vadd.xyz of the root position and the target offset (one asm run), then per group object reset + position copy + geometry update. Tricks: goto loop and an empty-asm launder on 100.0f stop constant hoisting; IdentityQuaternion/ZeroVector addresses are hoisted into locals like the Original's s5/s4. Remaining: launder adds mov.s (+2 words), and ordering of the hoisted address setup against the first lw. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));

extern char gcGlobalVar[];
extern s128 ZeroVector;
extern char IdentityQuaternion[];
extern char *GetLayoutClass(int);
extern int *isysGroupForFirst(void *, int);
extern int *isysGroupForNext(int *, int);
extern void isysGroupForExit(int, int);
extern void ForceUnparentLayoutObj(int);
extern void CallLayoutObjDebugResetFunc(int);
extern void ResetCharacterObj(int);
extern char *GetCharacterClass(int, void *);
extern void UpdateCharacterClassGeometry(char *, float);
extern void charrootdyn_getRegularColFinderPosition(char *, char *, int, int);
extern void UpdateCharacterClassPastGeometry(char *);
extern void SetCharacterObjDemoCutFinishFlag(int, int);
extern void UpdateLayoutClassSimpleGeometry(char *, float);
extern void GetClothDynamics(int, int, int, float, float);
extern void UpdateLayoutClassPastSimpleGeometry(char *);
extern void SetLayoutClassRootQuaternion(char *, void *);

#define F100(x) do { x = 100.0f; __asm__("" : "+f"(x)); } while (0)
void DebugSetHorsePositionWithTargetOfs(int obj, s128 *ofs)
{
    s128 pos;
    int *node;
    int cur;
    char *lay;
    char *chr;
    float k;
    char *iq;
    s128 *zv;

    lay = GetLayoutClass(obj);
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "lqc2 vf6, 0x0(%1)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%2)\n"
                         :
                         : "r"(*(s128 **)(lay + 0x134)), "r"(ofs), "r"(&pos)
                         : "memory");
    cur = 0;
    node = isysGroupForFirst(gcGlobalVar + 0x2B4, 0);
    if (node != 0) {
        iq = IdentityQuaternion;
        zv = &ZeroVector;
        cur = *node;
    again:
        {
            ForceUnparentLayoutObj(cur);
            CallLayoutObjDebugResetFunc(cur);
            ResetCharacterObj(cur);
            lay = GetLayoutClass(cur);
            if (lay != 0) {
                **(s128 **)(lay + 0x134) = pos;
                *(s128 *)(lay + 0x40) = pos;
                *(s128 *)(lay + 0x30) = *zv;
                chr = GetCharacterClass(cur, *(void **)(lay + 0x134));
                if (chr != 0) {
                    F100(k);
                    UpdateCharacterClassGeometry(chr, k);
                    charrootdyn_getRegularColFinderPosition(chr + 0x4C0, chr, *(int *)(lay + 0x13C), *(int *)(lay + 0x134));
                    UpdateCharacterClassPastGeometry(chr);
                    SetCharacterObjDemoCutFinishFlag(cur, 1);
                } else {
                    F100(k);
                    UpdateLayoutClassSimpleGeometry(lay, k);
                    GetClothDynamics(cur, 1, 0, 0.01f, 100.0f);
                    UpdateLayoutClassPastSimpleGeometry(lay);
                }
                SetLayoutClassRootQuaternion(lay, iq);
            }
            node = isysGroupForNext(node, 0);
            if (node != 0) {
                cur = *node;
                goto again;
            }
        }
    }
    if (cur != 0)
        isysGroupForExit(cur, 0);
}
#endif
