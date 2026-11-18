typedef struct { int object; int value; } SubObject;
typedef struct { int count; char pad4[0x14]; char *types; } AnimResource;
typedef struct { char pad[0x328]; AnimResource *res; int pad30c; int pad310; int pad314; SubObject *children; char pad33c[0x364 - 0x33C]; signed char locked; } ScriptAnimation;
extern int SetLayoutObjAccessSwitchThisObjOnly(void *, int);
extern void SetFogColAvailableFlag(int, int);
extern char *GetLayoutClass(int);
extern void *GetTwoWayLinkNext(void *);
extern unsigned char *GetTwoWayLinkData(void *);
extern int SetLayoutObjAccessSwitch(unsigned char *, int);

static inline ScriptAnimation *getScriptAnimation(unsigned char *object)
{
    if (object[8] == 13)
        return (ScriptAnimation *)(object + 0x20);
    return 0;
}

void SetScriptAnimationObjAccessSwitch(unsigned char *o, int sw)
{
    ScriptAnimation *anim = getScriptAnimation(o);
    int i;
    int n;

    if (anim->locked != 1 && SetLayoutObjAccessSwitchThisObjOnly(o, sw)) {
        ScriptAnimation *a = getScriptAnimation(o);
        AnimResource *res = a->res;
        i = 0;
        if (res->count > 0) {
            do {
                SubObject *c = (SubObject *)((i << 3) + (int)a->children);
                int t = i * 12;

                if (c->object != 0) {
                    SetLayoutObjAccessSwitchThisObjOnly((void *)c->object, sw);
                } else if (*(int *)(res->types + t) == 0x11) {
                    if (c->value != 0)
                        SetFogColAvailableFlag(c->value, sw);
                }
                i++;
            } while (i < a->res->count);
        }
    }
    n = anim->res->count;
    for (i = 0; i < n; i++) {
        int obj = anim->children[i].object;

        if (obj != 0) {
            void *link;

            for (link = GetTwoWayLinkNext(GetLayoutClass(obj) + 0x10C); link != 0; link = GetTwoWayLinkNext(link)) {
                unsigned char *d = GetTwoWayLinkData(link);

                if (d[8] != 9)
                    SetLayoutObjAccessSwitch(d, sw);
            }
        }
    }
}
