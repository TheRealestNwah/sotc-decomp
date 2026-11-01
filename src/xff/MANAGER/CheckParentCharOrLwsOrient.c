extern char *GetLayoutClass(void *);
extern char *GetScrLwsOriClass(void *);
extern void *GetGeometryPointerObject(void *);

typedef struct {
    char *obj;
    char pad4[0x4C];
} OriEntry;

int CheckParentCharOrLwsOrient(void *self, void *obj)
{
    int found = 0;
    char *lc = GetLayoutClass(obj);

    if (*(int *)(lc + 0x124) != 0) {
        char *ori = GetScrLwsOriClass(self);
        void *parent = GetGeometryPointerObject(lc + 0xC0);

        if (ori != 0) {
            OriEntry *e = *(OriEntry **)(ori + 0x1200);
            char *plc = GetLayoutClass(parent);
            int i;

            for (i = 0; i < *(int *)(*(char **)(ori + 0x11F8) + 0x30); i++, e++) {
                if (e->obj != 0 && e->obj + 0x20 == plc) {
                    found = 1;
                    break;
                }
            }
        } else {
            found = parent == self;
        }
    }
    return found;
}
