typedef struct { char pad[0x178]; float f178; char pad2[0xC]; float f188; char pad3[0x1E4]; char geo[1]; } G;
extern G gcGlobalVar;
extern char *GetCharacterClass(int);
extern char *GetLayoutClass(int);
extern int get_main_cameraman_camera_obj(void);
extern float ViewIntervalClip(int, int, float);
extern int StageManagerCheckAreaExist(int);
extern char *SCRGetGetGeometryPointerLegalParentObj(char *);
extern int ExecCharaGeometryPreprocess(int, float, float, float);
extern void ExecCharaGeometry(int, void *);
extern void ExecCharaGeometryPostprocess(int);

static inline int isLegalParent(char *l)
{
    char *p;

    if (l != 0 && *(int *)(l + 0x124) != 0
        && (p = SCRGetGetGeometryPointerLegalParentObj(l + 0xC0)) != 0) {
        switch (*(unsigned char *)(p + 8)) {
        case 9:
        case 0xD:
        case 0x16:
            return 1;
        }
    }
    return 0;
}

static void simpleExecCharaGeometry(int a0)
{
    int run = 0;
    char *c = GetCharacterClass(a0);
    float clip = ViewIntervalClip(a0, get_main_cameraman_camera_obj(), gcGlobalVar.f188);

    if (*(signed char *)(c + 0x534) != 0
        && (*(int *)(GetCharacterClass(a0) + 0x1170) == 0
            || StageManagerCheckAreaExist(*(int *)(GetLayoutClass(a0) + 0x134)) != 0
            || *(short *)(c + 0x370) == 4
            || isLegalParent(GetLayoutClass(a0))
            || *(unsigned char *)(c + 0xD90) == 1
            || *(int *)(c + 0x1070) == 1
            || *(short *)(c + 0x370) == 0xB))
        run = ExecCharaGeometryPreprocess(a0, gcGlobalVar.f178, clip, 1.0f / clip);
    if (run != 0) {
        c = GetCharacterClass(a0);
        ExecCharaGeometry(a0, (char *)&gcGlobalVar + 0x370);
        *(char *)(c + 0x539) = StageManagerCheckAreaExist(*(int *)(GetLayoutClass(a0) + 0x134));
    }
    ExecCharaGeometryPostprocess(a0);
}
