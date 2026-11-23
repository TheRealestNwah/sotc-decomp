typedef struct { int n; int pad[5]; int *kinds; } AnimHdr;
typedef struct { int id; int arg; } AnimEnt;
extern int ReparentChildObjects;
extern void ExecChildGroupManagerObj(void *, void *);
extern int GetObjectAnimationFloatFrame(void *, int, int, float, float);
extern void func_0008D6D0(void *, int, void *, void *, int, void *, int, int *, int, float, float);

static inline int isKind(int v)
{
    switch (v) {
    case 0xF ... 0x1C:
    case 0x20 ... 0x23:
        return 1;
    }
    return 0;
}

static void func_00090EC0(char *obj, int arg1, char *cls, float t, float dt)
{
    char buf[0x60];
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
}
