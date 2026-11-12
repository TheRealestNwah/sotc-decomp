typedef int s128 __attribute__((mode(TI)));

extern char B_0018B808[];
extern char RO_0017F678[];
extern char rootPtn[];
extern char IdentityQuaternion[];
extern char ZeroPoint[];
extern int ControlMode_PLAYER_DEFAULT;
extern int ScriptRequestEffectDef_PLA_SLIP;
extern char *GetCharacterClass(int);
extern int GetGeometryPointerCollisionDB(void *);
extern long *GetCollisionDBAttributeAdr(int);
extern void *GetGeometryPointerSurfacePlane(void *);
extern void GetQuaternionByAxisDirZY(void *, void *, void *);
extern void GetGeometryPointerPosition(void *, void *);
extern char *GetLayoutClass(int);
extern void UpdateLayoutClassSimpleGeometry(void *, void *, void *, float);
extern void isysRequestDeleteObj(int);
extern int initLayoutObj(void *, void *, int, void *);
extern void SetGeometryPointerNodePosState(void *, int, int, void *, void *);
extern void ExecEff(int, int, int, int, void *);

#ifdef NONMATCHING /* 113 diffs: calls, frame (0xB0) and pinned $s0..$s6 match; the original hoists the 0x750 load into the first branch delay slot and shares one gone=1 block, ours duplicates it into likely-branch delay slots, shifting the rest */
static void player_updateSlipEffect(int a00, char *st)
{
    register int a0 __asm__("$22") = a00;
    char sp[0x70] __attribute__((aligned(16)));
    register int gone __asm__("$19");
    char *cc;
    char *geo;
    int dbp;
    register long attr __asm__("$20");
    register char *qp __asm__("$21");
    int mk;
    int obj;

    gone = 0;
    cc = GetCharacterClass(a0);

    if (*(int *)(cc + 0x124) != 0 && *(signed char *)(cc + 0x10A1) != 0 && *(int *)(cc + 0x750) == ControlMode_PLAYER_DEFAULT
        && (geo = cc + 0xC0, dbp = GetGeometryPointerCollisionDB(geo), dbp != 0)) {
        {
            attr = *GetCollisionDBAttributeAdr(dbp);
            {
                char *plane = (char *)GetGeometryPointerSurfacePlane(geo);
                char *q = *(char **)(cc + 0x13C);
                __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                                     "vmul.xyzw vf5, vf4, vf4\n"
                                     "vmr32.xyzw vf6, vf4\n"
                                     "vmul.xyzw vf7, vf6, vf4\n"
                                     "vmr32.xyzw vf6, vf6\n"
                                     "vmul.xyzw vf8, vf6, vf4\n"
                                     "vsubx.z vf6, vf0, vf5x\n"
                                     "vsuby.z vf6, vf6, vf5y\n"
                                     "vaddw.y vf6, vf7, vf7w\n"
                                     "vsuby.x vf6, vf8, vf8y\n"
                                     "vsub.w vf6, vf0, vf0\n"
                                     "vadd.w vf5, vf0, vf0\n"
                                     "vmulw.xyz vf6, vf6, vf5w\n"
                                     "vaddw.z vf6, vf6, vf0w\n"
                                     "sqc2 vf6, 0x0(%0)\n"
                                     : : "r"(sp + 0x20), "r"(q) : "memory");
                mk = 0;
                qp = sp + 0x10;
                GetQuaternionByAxisDirZY(qp, plane, sp + 0x20);
            }
            GetGeometryPointerPosition(sp, geo);
            obj = *(int *)st;
            if (obj == 0) {
                mk = 1;
            } else {
                char *lc = GetLayoutClass(obj);
                *(s128 *)*(char **)(lc + 0x134) = *(s128 *)sp;
                *(s128 *)*(char **)(lc + 0x13C) = *(s128 *)(sp + 0x10);
                UpdateLayoutClassSimpleGeometry(lc, *(char **)(lc + 0x13C), *(char **)(lc + 0x134), 0.0f);
                if (*(long *)(st + 8) != attr) {
                    mk = 1;
                    isysRequestDeleteObj(*(int *)st);
                    *(int *)st = 0;
                }
            }
            if (mk != 0) {
                *(char **)(B_0018B808 + 4) = sp;
                *(char **)(B_0018B808 + 8) = qp;
                obj = initLayoutObj(RO_0017F678, rootPtn, 0, B_0018B808);
                SetGeometryPointerNodePosState(sp + 0x30, obj, 0, IdentityQuaternion, ZeroPoint);
                ExecEff(ScriptRequestEffectDef_PLA_SLIP, a0, a0, 0, sp + 0x30);
                *(int *)st = obj;
                *(long *)(st + 8) = attr;
            }
        }
    } else {
        gone = 1;
    }
    if (gone != 0) {
        obj = *(int *)st;
        if (obj != 0) {
            isysRequestDeleteObj(obj);
            *(int *)st = 0;
        }
    }
}
#endif
