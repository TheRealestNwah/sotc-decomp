typedef int s128 __attribute__((mode(TI)));

typedef struct {
    char pad0[0x60];
    s128 rot;
    s128 pos;
    char pad80[0x124 - 0x80];
    int parent;
    char pad128[0x134 - 0x128];
    s128 *posp;
    int pad138;
    s128 *rotp;
} LayoutClass;

extern LayoutClass *GetLayoutClass(void *);
extern void UpdateLayoutClassParentSimpleGeometry(LayoutClass *);
extern void UpdateLayoutClassSimpleGeometry(LayoutClass *, float);

int SCRSetLWSGeometryWithNoParentChange(void *arg0, s128 *pos, s128 *rot)
{
    LayoutClass *l = GetLayoutClass(arg0);

    *l->posp = *pos;
    *l->rotp = *rot;
    if (l->parent != 0) {
        l->rot = *rot;
        l->pos = *pos;
        UpdateLayoutClassParentSimpleGeometry(l);
    }
    UpdateLayoutClassSimpleGeometry(l, 0.0f);
    return 1;
}
