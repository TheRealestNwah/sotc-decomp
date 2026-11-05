extern int LoaderSysLoadIopModule(const char *path, int argsLen, const char *args);
extern void setNewIopIdentifier(const char *name);
extern char D_00136DE0[], D_00136E00[], D_00136E20[], D_00136E68[], D_00136E88[];
extern char D_00136EA0[], D_00136EC0[], D_00136EE0[], D_00136F00[], D_00136F20[], D_00136F40[];
extern char D_00136F60[], D_00136F78[], D_00136F98[], D_00136FB8[], D_00136FD8[];
extern char D_0013A088[], D_0013A090[], D_0013A098[], D_0013A0A0[], D_0013A0A8[], D_0013A0B0[];
extern char D_0013A0B8[], D_0013A0C0[], D_0013A0C8[], D_0013A0D0[], D_0013A0D8[], D_0013A0E0[];

#define LOAD(path, len, args, id)                          \
    if (LoaderSysLoadIopModule(path, len, args) < 0) {     \
        return -1;                                         \
    }                                                      \
    setNewIopIdentifier(id)

int func_00104090(int mode) {
    LOAD(D_00136DE0, 0, 0, D_0013A088);
    LOAD(D_00136E00, 0x46, D_00136E20, D_0013A090);
    LOAD(D_00136E68, 0x14, D_00136E88, D_0013A098);
    switch (mode) {
    case 1:
    case 2:
        LOAD(D_00136EA0, 0, 0, D_0013A0A0);
        LOAD(D_00136EC0, 0, 0, D_0013A0A8);
        break;
    case 5:
        LOAD(D_00136EA0, 0, 0, D_0013A0A0);
        break;
    case 3:
    case 4:
        LOAD(D_00136EE0, 0, 0, D_0013A0B0);
        LOAD(D_00136F00, 0, 0, D_0013A0B8);
        break;
    case 0:
        break;
    }
    switch (mode) {
    case 2:
    case 4:
        LOAD(D_00136F20, 0, 0, D_0013A0C0);
        LOAD(D_00136F40, 0, 0, D_0013A0C8);
        break;
    case 5:
        LOAD(D_00136F20, 0, 0, D_0013A0C0);
        LOAD(D_00136F60, 1, D_0013A0D0, D_0013A0D0);
        break;
    case 0:
        LoaderSysLoadIopModule(D_00136EA0, 0, 0);
        LoaderSysLoadIopModule(D_00136EC0, 0, 0);
        LoaderSysLoadIopModule(D_00136EE0, 0, 0);
        LoaderSysLoadIopModule(D_00136F00, 0, 0);
        LoaderSysLoadIopModule(D_00136F20, 0, 0);
        LoaderSysLoadIopModule(D_00136F40, 0, 0);
        break;
    }
    LOAD(D_00136F78, 0, 0, D_0013A0D8);
    LOAD(D_00136F98, 0, 0, D_0013A0E0);
    LOAD(D_00136FB8, 0, 0, D_00136FD8);
    return 0;
}
