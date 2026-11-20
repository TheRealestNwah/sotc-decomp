typedef int s128 __attribute__((mode(TI)));

extern struct { int x; void *pos; void *rot; } B_0018B808;
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


typedef struct { char b[0x10]; } __attribute__((aligned(16))) Q;
/* Quad stores through a union with a pointer member, so the 0x13C load stays after the first store. */
typedef union { s128 q; char *p; } QU;
static inline void setPR(char *lc, Q *pos, Q *rot)
{
    register char *p __asm__("$6");
    register char *r __asm__("$5");
    p = *(char **)(lc + 0x134);
    ((QU *)p)->q = *(s128 *)pos;
    r = *(char **)(lc + 0x13C);
    ((QU *)r)->q = *(s128 *)rot;
    UpdateLayoutClassSimpleGeometry(lc, r, p, 0.0f);
}
static void player_updateSlipEffect(int a00, char *st)
{
    register int a0 __asm__("$22") = a00;
    Q pos;
    Q rot;
    Q tmp;
    char mat[0x40] __attribute__((aligned(16)));
    register int gone __asm__("$19");
    char *cc;
    int mode;
    char *geo;
    int dbp;

    gone = 0;
    cc = GetCharacterClass(a0);
    mode = *(int *)(cc + 0x750);
    if (*(int *)(cc + 0x124) != 0 && *(signed char *)(cc + 0x10A1) != 0 && mode == ControlMode_PLAYER_DEFAULT
        && (geo = cc + 0xC0, dbp = GetGeometryPointerCollisionDB(geo), dbp != 0)) {
        {
            register long attr __asm__("$20");
            register Q *qp __asm__("$21");
            int obj;
            char *plane;
            int mk;
            attr = *GetCollisionDBAttributeAdr(dbp);
            plane = (char *)GetGeometryPointerSurfacePlane(geo);

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
                                 : : "r"(&tmp), "r"(*(char **)(cc + 0x13C)) : "memory");
            mk = 0;
            qp = &rot;
            GetQuaternionByAxisDirZY(qp, plane, &tmp);
            GetGeometryPointerPosition(&pos, geo);
            if (*(int *)st != 0) {
                setPR(GetLayoutClass(*(int *)st), &pos, &rot);
                if (*(long *)(st + 8) != attr) {
                    mk = 1;
                    isysRequestDeleteObj(*(int *)st);
                    *(int *)st = 0;
                }
            } else {
                mk = 1;
            }
            if (mk != 0) {
                B_0018B808.pos = &pos;
                B_0018B808.rot = qp;
                obj = initLayoutObj(RO_0017F678, rootPtn, 0, &B_0018B808);
                /* The empty asm keeps &mat out of a saved register (recomputed for ExecEff). */
                { char *q = mat; __asm__("" : "+r"(q)); SetGeometryPointerNodePosState(q, obj, 0, IdentityQuaternion, ZeroPoint); }
                ExecEff(ScriptRequestEffectDef_PLA_SLIP, a0, a0, 0, mat);
                *(int *)st = obj;
                *(long *)(st + 8) = attr;
            }
        }
    } else {
        gone = 1;
    }
    if (gone != 0) {
        int o = *(int *)st;
        if (o != 0) {
            isysRequestDeleteObj(o);
            *(int *)st = 0;
        }
    }
}
