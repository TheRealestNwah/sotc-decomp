/* Parked: 13 diffs, 101 words. Horse reposition debug: VU0 vadd.xyz of the root position and the target offset (one asm run), then per group object reset + position copy + geometry update. Tricks: a real do-while loop (its loop note gives the Original's alignment nop before the loop head, and the else label then lands 8-aligned without padding), +0x40 copied from the just-stored root position so the pos reload matches, IdentityQuaternion/ZeroVector addresses hoisted into locals like the Original's s5/s4. Remaining: the 0x134 pointer loaded into v1 and copied to a1 (the Original loads it straight into a1), and argument setup order for charrootdyn_getRegularColFinderPosition and GetClothDynamics (the Original sets them up last argument first). */
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
extern void GetClothDynamics(int, float, int, int, float);
extern void UpdateLayoutClassPastSimpleGeometry(char *);
extern void SetLayoutClassRootQuaternion(char *, void *);

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
        do {
            cur = *node;
            ForceUnparentLayoutObj(cur);
            CallLayoutObjDebugResetFunc(cur);
            ResetCharacterObj(cur);
            lay = GetLayoutClass(cur);
            if (lay != 0) {
                **(s128 **)(lay + 0x134) = pos;
                *(s128 *)(lay + 0x40) = **(s128 **)(lay + 0x134);
                *(s128 *)(lay + 0x30) = *zv;
                chr = GetCharacterClass(cur, *(void **)(lay + 0x134));
                k = 100.0f;
                if (chr != 0) {
                    UpdateCharacterClassGeometry(chr, k);
                    charrootdyn_getRegularColFinderPosition(chr + 0x4C0, chr, *(int *)(lay + 0x13C), *(int *)(lay + 0x134));
                    UpdateCharacterClassPastGeometry(chr);
                    SetCharacterObjDemoCutFinishFlag(cur, 1);
                } else {
                    UpdateLayoutClassSimpleGeometry(lay, k);
                    GetClothDynamics(cur, 0.01f, 1, 0, 100.0f);
                    UpdateLayoutClassPastSimpleGeometry(lay);
                }
                SetLayoutClassRootQuaternion(lay, iq);
            }
            node = isysGroupForNext(node, 0);
        } while (node != 0);
    }
    if (cur != 0)
        isysGroupForExit(cur, 0);
}
#endif
