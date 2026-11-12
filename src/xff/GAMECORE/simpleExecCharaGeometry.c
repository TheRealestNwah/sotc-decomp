extern char gcGlobalVar[];
extern char *GetCharacterClass(int);
extern char *GetLayoutClass(int);
extern int get_main_cameraman_camera_obj(void);
extern float ViewIntervalClip(int, int, float);
extern int StageManagerCheckAreaExist(int);
extern char *SCRGetGetGeometryPointerLegalParentObj(char *);
extern int ExecCharaGeometryPreprocess(int, float, float, float);
extern void ExecCharaGeometry(int, void *);
extern void ExecCharaGeometryPostprocess(int);

#ifdef NONMATCHING /* 81 diffs: structure and field widths right; the original keeps only the %hi of gcGlobalVar live in $s3 across the calls (+%lo added per use), ours materializes the full pointer, and the area-flag temporaries sit in other registers */
static void simpleExecCharaGeometry(int a0)
{
    int run = 0;
    char *g = gcGlobalVar;
    char *c = GetCharacterClass(a0);
    float clip = ViewIntervalClip(a0, get_main_cameraman_camera_obj(), *(float *)(g + 0x188));
    char *l;
    char *p;
    int ok;

    if (*(signed char *)(c + 0x534) != 0) {
        if (*(int *)(GetCharacterClass(a0) + 0x1170) != 0
            && StageManagerCheckAreaExist(*(int *)(GetLayoutClass(a0) + 0x134)) == 0
            && *(short *)(c + 0x370) != 4) {
            l = GetLayoutClass(a0);
            ok = 0;
            if (l != 0) {
                if (*(int *)(l + 0x124) == 0) {
                    ok = 0;
                } else {
                    p = SCRGetGetGeometryPointerLegalParentObj(l + 0xC0);
                    if (p == 0) {
                        ok = 0;
                    } else {
                        unsigned char t = *(unsigned char *)(p + 8);

                        ok = 1;
                        if (t != 0xD) {
                            if (t < 0xE) {
                                if (t != 9)
                                    ok = 0;
                            } else if (t != 0x16) {
                                ok = 0;
                            }
                        }
                    }
                }
            }
            if (ok != 0 || *(unsigned char *)(c + 0xD90) == 1 || *(int *)(c + 0x1070) == 1 || *(short *)(c + 0x370) == 0xB)
                run = ExecCharaGeometryPreprocess(a0, *(float *)(g + 0x178), clip, 1.0f / clip);
        } else {
            run = ExecCharaGeometryPreprocess(a0, *(float *)(g + 0x178), clip, 1.0f / clip);
        }
    }
    if (run != 0) {
        c = GetCharacterClass(a0);
        ExecCharaGeometry(a0, g + 0x370);
        *(char *)(c + 0x539) = StageManagerCheckAreaExist(*(int *)(GetLayoutClass(a0) + 0x134));
    }
    ExecCharaGeometryPostprocess(a0);
}
#endif
