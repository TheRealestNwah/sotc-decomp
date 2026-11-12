extern void *DldSysUndefSymbol;
extern char _GameObject[];
extern char gcGlobalVar[];
extern char backStageGobjSave[];
extern int gStatGObjDispChk(char *);
extern int gStatGobjDispGflagChk(char *);
extern void getStageLayoutGeometryPointer(void *, int, void *);
extern int backStageGobjCheckEntry(char *, int);
extern int backStageGobjLoad(void *, char *, char *);
extern void GetQuaternionByDegEulerYXZ(void *, float, float, float);
extern void setTreeId(int);
extern void resetTreeId(void);
extern int loadObj(void *, void *, void *, void *, int, int);

static inline char *dldBase(unsigned int *reference)
{
    unsigned int encoded = *reference;
    unsigned int offset = encoded & 0x3FFFF;
    char *module;
    if (offset)
        module = *(char **)((char *)reference - offset);
    else
        module = 0;
    if (module == 0 || module == DldSysUndefSymbol)
        return 0;
    return module;
}

static inline char *resourceData(unsigned int *reference)
{
    char *module = dldBase(reference);
    if (module) {
        int index = (*reference >> 18) & 0xFFF;
        char *definition = *(char **)(module + 8);
        char *data = *(char **)(module + 0x10);
        return data + index * *(int *)(definition + 0xC);
    }
    return 0;
}

#ifdef NONMATCHING /* 249 diffs, same word count: stack layout of the loadObj request (orig scatters it at $sp+0x40..0x78) and dld-resolve branch forms */
int func_00026238(int arg0, char *r, float *off, int flag, int flag2)
{
    float rot[4] __attribute__((aligned(16)));
    float pos[4] __attribute__((aligned(16)));
    int req[24] __attribute__((aligned(16)));
    float geo[8] __attribute__((aligned(16)));
    unsigned int *s3 = (unsigned int *)(r + 4);
    char *mod = dldBase(s3);
    char *s5, *s4, *s1, *g;
    char *v1;
    int disp, t0;

    if (mod == 0 || *(char **)(mod + 8) != _GameObject)
        return 0;
    s5 = *(char **)(dldBase(s3) + 0x10);
    v1 = dldBase((unsigned int *)(r + 0xC));
    if (v1)
        v1 = *(char **)(v1 + 0x10);
    s1 = v1 ? *(char **)(v1 + 8) : 0;
    *(int *)(r + 0x48) = 0;
    if (v1 == 0 && s1 == 0)
        return 1;
    if (flag == 0 && v1 == 0)
        return 0;
    s4 = resourceData((unsigned int *)(s5 + 0x10));
    disp = 0;
    if (s4 && gStatGObjDispChk(s4))
        disp = 1;
    if (*(int *)r == 0 || disp == 0)
        return 0;
    g = 0;
    if (s1) {
        getStageLayoutGeometryPointer(geo, (int)s1, r + 0x10);
        g = (char *)geo;
    }
    if (backStageGobjCheckEntry(s5, 0)) {
        if (backStageGobjLoad(req, s5, r)) {
            ((float *)(req))[0x98 / 4 - 0x80 / 4] += off[0];
            ((float *)(req))[0x9C / 4 - 0x80 / 4] -= off[1];
            ((float *)(req))[0xA0 / 4 - 0x80 / 4] += off[2];
        }
    }
    GetQuaternionByDegEulerYXZ(rot, *(float *)(g + 0x24), -*(float *)(g + 0x28), *(float *)(g + 0x2C));
    req[0x10 / 4] = (int)off;
    req[0x14 / 4] = (int)pos;
    req[0x18 / 4] = (int)rot;
    req[0x20 / 4] = (int)g;
    req[0x30 / 4] = 0;
    req[0x34 / 4] = (int)resourceData((unsigned int *)(r + 0x3C));
    *(float *)&req[0x38 / 4] = *(float *)(g + 0x40);
    req[0x3C / 4] = *(int *)(g + 0x44);
    req[0x44 / 4] = (int)resourceData(s3);
    req[0x48 / 4] = (int)backStageGobjSave;
    req[0x4C / 4] = 1;
    req[0x50 / 4] = *(int *)(g + 0x14);
    req[0x54 / 4] = 0;
    req[0x58 / 4] = 0;
    if (*(short *)(s5 + 0xC) >= 0)
        setTreeId(*(short *)(s5 + 0xC));
    t0 = 0;
    if (s4)
        t0 = gStatGobjDispGflagChk(s4);
    *(int *)(r + 0x48) = loadObj(s3, req, (void *)arg0, flag2 ? gcGlobalVar + 0x280 : 0, t0, 4);
    if (*(short *)(s5 + 0xC) >= 0)
        resetTreeId();
    return 0;
}
#endif
