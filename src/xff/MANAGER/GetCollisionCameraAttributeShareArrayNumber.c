extern int CheckLegalCollisionGP(char *);
extern char *GetGeometryPointerCollisionDB(char *);
extern char *GetLayoutClass(void *);

int GetCollisionCameraAttributeShareArrayNumber(char *gp)
{
    char *db;
    char *layout;
    char *metadata;
    int count;
    void *owner;

    if (CheckLegalCollisionGP(gp)) {
        db = GetGeometryPointerCollisionDB(gp);
        layout = GetLayoutClass(*(void **)db);
        metadata = *(char **)(*(char **)(layout + 0x184) + 0x20);
        count = -1;
        if (*(int *)metadata >= 5 && *(int *)(metadata + 0x44) != 0) {
            owner = *(void **)db;
            if (owner != 0)
                GetLayoutClass(owner);
            count = 1;
        }
        return count >= 0 ? count : 1;
    }
    return -1;
}
