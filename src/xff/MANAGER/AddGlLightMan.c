typedef struct {
    char p0[0x2C];
    int enable;
    unsigned char mode;
    char p31[0xF];
} LightSlot;

typedef struct {
    LightSlot slots[3];
    char pC0[0x50];
    int flags;
    char *name;
    char p118[8];
    int p120;
    int p124;
    char p128[0x1C];
    int p144;
} GlobalLightWork;

typedef struct {
    int p0;
    int name;
} GlobalLightDef;

extern char *GetLightColMan();
extern void **isysGroupForFirst(void *, int);
extern void **isysGroupForNext(void **, int);
extern void isysGroupForExit(void *, int);
extern void isysAddGroupWithLinkParam(void *, void *, int, int);
extern void _isysDeleteGroup(void *, void *, int);
extern int strcmp(const char *, const char *);
extern int func_0007C670(GlobalLightWork *, GlobalLightDef *, int);

GlobalLightWork *AddGlLightMan(GlobalLightDef *def, int arg)
{
    char *man;
    GlobalLightWork *w = 0;
    int found;
    int pass;

    man = GetLightColMan(def);
    found = 0;
    for (pass = 0; pass < 2; pass++) {
        void **node;
        unsigned char *last;

        if (found) {
            continue;
        }
        last = 0;
        for (node = isysGroupForFirst(pass == 0 ? man + 0x518 : man + 0x514, 0); node != 0;
             node = isysGroupForNext(node, 0)) {
            char *lman;
            int match;
            int i;
            LightSlot *slot;

            last = *node;
            w = (GlobalLightWork *)(last[8] == 0x19 ? last + 0x20 : 0);
            match = 0;
            lman = GetLightColMan();
            if (pass == 1) {
                for (i = 0; i < 3; i++) {
                    slot = &w->slots[i];
                    slot->enable = 0;
                    slot->mode = 3;
                }
                w->flags = 0;
                w->name = (char *)def->name;
                w->p124 = 0;
                w->p120 = 0;
                w->p144 = 1;
                isysAddGroupWithLinkParam(last, lman + 0x518, 0, 0);
                _isysDeleteGroup(last, lman + 0x514, 0);
                w->flags |= 0x1000;
            }
            if (strcmp(w->name, (char *)def->name) == 0 && func_0007C670(w, def, arg) != 0) {
                match = 1;
            }
            if (match) {
                found = 1;
                break;
            }
        }
        if (last != 0) {
            isysGroupForExit(last, 0);
        }
    }
    *(int *)(man + 0x52C) |= 1;
    return found ? w : 0;
}
