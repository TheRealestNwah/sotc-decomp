extern char gcGlobalVar[];
extern char rootPtn[];
extern char st_collisionalias[];
extern char st_motionsyncanimation[];
extern void *initScriptCharObj(void *, void *, void *, int, void *, void *, void *, int);
extern int isysAddGroupWithLinkParam(void *, void *, int, int);

void *SCRCreateScriptCharObj(void *a, char *param)
{
    char *list = gcGlobalVar + 0x280;
    void *obj;

    *(int *)(param + 0x1C) = 1;
    *(int *)(param + 0x10) = 1;
    *(int *)(param + 0x2C) = 1;
    obj = initScriptCharObj(rootPtn, a, param, 4, list, st_collisionalias, st_motionsyncanimation, 1);
    if (obj != 0) {
        isysAddGroupWithLinkParam(obj, list + 4, 0, 0);
        isysAddGroupWithLinkParam(obj, list - 0x10, 0, 0);
    }
    return obj;
}
