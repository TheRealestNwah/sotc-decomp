typedef struct {
    short type;
    char pad[6];
    int count;
    char pad2[0x30 - 0xC];
    char *name;
} ClothChild;

typedef struct {
    char *v[15]; /* char *, so the stores may alias c->name and keep its load after them */
} InitParam;

typedef struct {
    char pad[0x178];
    char **groups;
    char pad2[4];
    ClothChild *children;
} LayoutClass;

extern LayoutClass *GetLayoutClass(void);
extern void *SearchLayoutObjDefByName(void *, char *);
extern void *initLayoutObj(char *, void *, void *, void *);
extern void *initLayoutObjVU0Secure(char *, void *, void *, void *);
extern void isysAddGroupWithLinkParam(void *, void *, int, int);
extern char rootPtn[];

static inline void initParam(InitParam *p, int type)
{
    p->v[7] = (char *)type;
    p->v[0] = 0;
    p->v[1] = 0;
    p->v[2] = 0;
    p->v[3] = 0;
    p->v[8] = 0;
    p->v[4] = 0;
    p->v[5] = 0;
    p->v[6] = 0;
    p->v[9] = 0;
    p->v[10] = 0;
    p->v[11] = 0;
    p->v[12] = 0;
    p->v[13] = 0;
    p->v[14] = 0;
}

void CreateClothChildLayoutObj(void *a0, char *res, int secure)
{
    LayoutClass *lc = GetLayoutClass();
    ClothChild *c = lc->children;
    ClothChild *p;
    char *grp;
    int count;
    int i;
    void *def;
    InitParam param;

    if (c == 0)
        return;
    p = c;
    count = 0;
    for (; p->type >= 0; p++)
        count++;
    grp = *lc->groups;
    for (i = 0; i < count; i++, c++, grp += 0x90) {
        if (c->type == 1) {
            initParam(&param, c->type);
            def = SearchLayoutObjDefByName(res + 0xC, c->name);
            if (def != 0) {
                int n = c->count - 1;
                if (secure) {
                    while (n--)
                        isysAddGroupWithLinkParam(initLayoutObjVU0Secure(c->name, rootPtn, def, &param), grp + 8, 0, 0);
                } else {
                    while (n--)
                        isysAddGroupWithLinkParam(initLayoutObj(c->name, rootPtn, def, &param), grp + 8, 0, 0);
                }
            }
        }
    }
}
