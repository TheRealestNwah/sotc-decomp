extern void func_00092988(void);
extern int GetLwsOrientNodeNum(int);
extern void *_isysCreateObj(void *, int, int, int, int, int);
extern int DldSysUndefSymbol;
extern void *iosMallocAlign(void *, int, int);
extern void *SearchLayoutObjDefByName(void *, char *);
extern void *get_particle_effect_id_by_name(void *, char *);
extern int is_loop_particle(void *);
extern void *GetDamageDefByName(void *, char *);
extern void *get_wind_effect_data(void *, char *);
extern int is_eternal_wind(void *);
extern void *getAnimationDefByName(void *, char *);
extern void *GetAnimationEffectDefByName(void *, char *);
extern void *get_camera_lws_animation_parameter_by_name(void *, char *);
extern int is_loop_camera_lws_animation(void *);
extern void *get_camera_region_resource_id_by_name(void *, char *);

typedef struct { int type; int name; int pad; } Node;
typedef struct { int loop; int type; void *ptr; } Ent;

static void func_00092388(int **res, unsigned char *o, void *grp)
{
    char *cls;
    char *lws;
    Node *node;
    Node *nodes;
    char *r2;
    int n;
    int *h;
    int off;
    char *t;
    char *d;
    Ent *e;
    Ent *ents;
    unsigned int i;
    void *p;
    char *name;
    int type;

    cls = 0;
    if (o[8] == 0x17)
        cls = (char *)o + 0x20;
    lws = *(char **)((char *)res[0] + 0x20);
    r2 = (char *)res[2];
    nodes = *(Node **)(lws + 0x10);
    n = GetLwsOrientNodeNum((int)lws);
    h = (int *)(r2 + 0x10);
    node = nodes;
    off = *h & 0x3FFFF;
    t = off != 0 ? *(char **)((char *)h - off) : 0;
    d = (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) : 0;
    ents = iosMallocAlign(*(void **)o, n * 12, 0x10);
    *(Ent **)(cls + 0x54) = ents;
    e = ents;
    if (d == 0)
        return;
    for (i = 0; i < n; i++, node++, e++) {
        name = (char *)node->name;
        p = 0;
        e->loop = 0;
        type = node->type;
        e->type = type;
        switch (type) {
        case 1:
        case 5:
            p = SearchLayoutObjDefByName(d + 8, name);
            break;
        case 2:
        case 45:
            p = get_particle_effect_id_by_name(d + 0xC, name);
            if (p != 0 && is_loop_particle(p) == 1)
                e->loop = 1;
            break;
        case 3:
        case 10:
        case 13:
            p = GetDamageDefByName(d + 0x10, name);
            break;
        case 4:
        case 47:
        case 48:
            p = get_wind_effect_data(d + 0x14, name);
            if (p != 0 && is_eternal_wind(p))
                e->loop = 1;
            break;
        case 9:
            p = getAnimationDefByName(d + 4, name);
            break;
        case 6:
        case 38:
            p = (void *)1;
            break;
        case 11:
            p = GetAnimationEffectDefByName(d + 0x20, name);
            break;
        case 12:
            p = GetAnimationEffectDefByName(d + 0x24, name);
            break;
        case 7:
            p = get_camera_lws_animation_parameter_by_name(d + 0x18, name);
            if (p != 0 && is_loop_camera_lws_animation(p))
                e->loop = 1;
            break;
        case 39:
        case 40:
        case 41:
        case 42:
            p = get_camera_region_resource_id_by_name(d + 0x1C, name);
            if (p != 0)
                e->loop = 1;
            break;
        }
        e->ptr = p;
    }
}

void *CreateScriptLwsOrientDefObj(void *grp, int size, int **res)
{
    int n = GetLwsOrientNodeNum(*(int *)((char *)*res + 0x20)) * 12 + 0x33;
    void *o = _isysCreateObj(grp, 0x17, 0x80, size + n, (int)func_00092988, 0x10);

    func_00092388(res, o, grp);
    return o;
}
