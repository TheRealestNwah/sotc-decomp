/* Animation kinds 0xF-0x1C and 0x20-0x23 update even without a bound id. */
typedef struct { int n; int pad[5]; int *kinds; } AnimHdr;
typedef struct { int id; int arg; } AnimEnt;
extern void iosResetCpuRapCounter(int);
extern int GetDamageClass(void *);
extern void ResetDamageClass(int);
extern void CheckLetter(void *, void *);
extern int CheckDamageLetter;
extern int ReparentChildObjects;
extern void ExecChildGroupManagerObj(void *, void *);
extern int func_0008BF90(void *, float, float);
extern void func_00088858(void *, float);
extern void UpdateLayoutClassSimpleGeometry(void *, float);
extern int GetObjectAnimationFloatFrame(void *, int, int, float, float);
extern void func_0008D6D0(void *, int, void *, void *, int, void *, int, int *, int, float, float);
extern char *GetLayoutClass(int);
extern void GetLayoutClassWindGeometry(char *, char *);
extern void GetClothDynamics(int, float, float, int, int);

static inline int isKind(int v)
{
    switch (v) {
    case 0xF ... 0x1C:
    case 0x20 ... 0x23:
        return 1;
    }
    return 0;
}

int ExecObjectAnimation(char *obj, int arg1, float t, float dt)
{
    char buf[0x60];
    int ret;
    char *cls = (unsigned char)obj[8] == 0xD ? obj + 0x20 : 0;
    int d;

    iosResetCpuRapCounter(1);
    d = GetDamageClass(obj);
    ret = 0;
    ResetDamageClass(d);
    CheckLetter(obj, &CheckDamageLetter);
    if (t != 0.0f && *(signed char *)(cls + 0x364) != 1) {
        void (*cb)(void *, int);
        ret = func_0008BF90(obj, t, dt);
        func_00088858(cls, dt);
        cb = *(void (**)(void *, int))(cls + 0x358);
        if (cb != 0) {
            cb(obj, *(int *)(cls + 0x35C));
            UpdateLayoutClassSimpleGeometry(cls + 0x70, dt);
        }
        if (*(signed char *)(cls + 0x368) == 0 || *(signed char *)(cls + 0x369) == 0) {
            AnimHdr *h = *(AnimHdr **)(cls + 0x328);
            char *fp = cls + 0x2E0;
            int n = h->n;
            float f0 = ((float *)fp)[2];
            float f1 = ((float *)fp)[3];
            int *kind = h->kinds;
            int anim = *(int *)(cls + 0x334);
            AnimEnt *e = *(AnimEnt **)(cls + 0x338);
            int i;
            for (i = 0; i < n; i++) {
                int id = e->id;
                if (id != 0 || isKind(*kind)) {
                    GetObjectAnimationFloatFrame(buf, anim, i, f0, f1);
                    func_0008D6D0(cls, id, obj, obj, 0, buf, arg1, kind, e->arg, t, dt);
                }
                e++;
                kind += 3;
            }
            ExecChildGroupManagerObj(obj, &ReparentChildObjects);
            *(signed char *)(cls + 0x369) = 1;
        }
        {
            if (*(int *)(cls + 0x34C) != 0) {
                int *p = *(int **)(cls + 0x354);
                int cnt = *(int *)(cls + 0x34C);
                while (cnt--) {
                    int o = *p++;
                    char *lc = GetLayoutClass(o);
                    GetLayoutClassWindGeometry(lc, lc + 0x30);
                    GetClothDynamics(o, t, dt, 1, 0);
                }
            }
        }
    }
    return ret;
}
