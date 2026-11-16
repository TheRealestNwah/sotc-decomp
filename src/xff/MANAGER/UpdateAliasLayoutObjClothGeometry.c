extern char *GetScriptLayoutClass(void *);
extern void *dynamic_cast_to_camera_obj(void *);
extern char *get_camera_obj_layout_class(void *);
extern char *GetLightClass(void *);

static inline char *layoutClass(unsigned char *o)
{
    switch (o[8]) {
    case 0xA:
        return (char *)o + 0x20;
    case 0xB:
        return GetScriptLayoutClass(o) + 0x70;
    case 0x11:
        return get_camera_obj_layout_class(dynamic_cast_to_camera_obj(o));
    case 0x13:
        return GetLightClass(o);
    case 9:
    case 0xD:
    case 0x16:
        return (char *)o + 0x90;
    default:
        return 0;
    }
}

typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } V;
typedef struct { char pad[0x60]; V v60; V v70; V v80; } Cloth;
extern V ZeroVector;
typedef struct { char pad[0x180]; int x180; char pad2[0x10]; unsigned char *alias; char pad3[4]; Cloth *cloth; } LC;

void UpdateAliasLayoutObjClothGeometry(unsigned char *o)
{
    LC *l = (LC *)layoutClass(o);
    LC *s;

    if (l->x180 == 0)
        return;
    s = (LC *)layoutClass(l->alias);
    if (s->cloth != 0) {
        l->cloth->v80.f[0] = s->cloth->v80.f[0];
        l->cloth->v80.f[1] = s->cloth->v80.f[1];
        l->cloth->v60.q = s->cloth->v60.q;
        l->cloth->v70.q = s->cloth->v70.q;
    } else {
        l->cloth->v80.f[0] = 0.0f;
        l->cloth->v80.f[1] = 0.0f;
        l->cloth->v60.q = ZeroVector.q;
        l->cloth->v70.q = ZeroVector.q;
    }
}
