typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } Vec4;

extern char gcGlobalVar[];
extern float D_0017A2B8[];
extern void *SCRGetFirstObj(void *);
extern char *GetLayoutClass(void *);
extern char *GetCharacterClass(void *);
extern int ClipCollisionDirect(void *, float *, float *, void *);
extern long nico_GetGeometryPointerAttr(void *);

int checkReadyPlayerCollision(void)
{
    char buf[0x50] __attribute__((aligned(16)));
    Vec4 from;
    Vec4 to;
    Vec4 pos;
    void *obj;
    char *cc;
    int i;
    int j;

    obj = SCRGetFirstObj(gcGlobalVar + 0x2B0);
    if (obj == 0)
        return 0;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            from.q = (*(Vec4 **)(GetLayoutClass(obj) + 0x134))->q;
            from.f[0] += D_0017A2B8[i];
            from.f[2] += D_0017A2B8[j];
            to.q = from.q;
            from.f[1] += 1000.0f;
            to.f[1] -= 1000.0f;
            cc = GetCharacterClass(obj);
            if (ClipCollisionDirect(buf, from.f, to.f, (void *)(*(int *)(cc + 0xE38) + *(short *)(GetCharacterClass(obj) + 0x370) * 4)) == 0
                || (nico_GetGeometryPointerAttr(buf) & 0x2000000) != 0)
                return 0;
        }
    }
    pos.q = (*(Vec4 **)(GetLayoutClass(obj) + 0x134))->q;
    pos.f[1] = *(float *)(buf + 0x44) + *(float *)(*(char **)(GetCharacterClass(obj) + 0x358) + 0x14);
    return 1;
}
