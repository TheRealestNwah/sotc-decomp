extern void *GetCharacterClass(void *);
extern void *GetLayoutClass(void *);

#define NULL ((void *)0)
extern void DispCloth(int);
extern void func_00078778(void *, void *, void *);
extern void func_00078A60(void *, void *, void *);
extern void func_00078C28(void *, void *, void *);
extern int D_00136BE4;
extern int D_00136BE8;

void DispLayoutObjModel(void *arg0, void *arg1) {
    void *temp_s1;
    void *temp_v0;

    temp_s1 = GetCharacterClass(arg1);
    temp_v0 = GetLayoutClass(arg1);
    if ((*(int *)((char *)((*(void **)((char *)((*(void **)((char *)((*(void **)((char *)(temp_v0) + 0x144))) + 0))) + 0x20))) + 0x18)) & 1) {
        func_00078A60(arg0, temp_v0, temp_s1);
        if (temp_s1 != NULL) {
            if (((*(signed char *)((char *)(temp_s1) + 0x10A5)) != 0) && (D_00136BE8 == 0)) {
                func_00078C28(GetLayoutClass(arg0), temp_s1, temp_v0);
            }
        }
    } else {
        func_00078778(arg0, temp_v0, temp_s1);
    }
    if (D_00136BE4 == 0) {
        return;
    }
    if ((*(int *)((char *)(temp_v0) + 0x180)) == 0) {
        return;
    }
    if ((*(long *)((char *)((*(void **)((char *)(temp_v0) + 0x144))) + 0x260)) & 0x80) {
        return;
    }
    DispCloth((*(int *)((char *)(temp_v0) + 0x178)));
}
