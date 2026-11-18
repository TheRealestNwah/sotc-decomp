extern int D_0017AD3C;
extern int DldSysUndefSymbol;
extern char IdentityQuaternion[];
extern int ScriptAnimationObjDef_HOME_ITEM_LIGHTNING_END;
extern char gcGlobalVar[];
extern char *GetLayoutClass(int);
extern int SCRGetGetGeometryPointerLegalParentObj(void *);
extern int SCRGetFirstObj(void *);
extern int _SCRSetupLWS(int, int, void *, void *, int);
extern void _SCRStartLWS(int, int, int, int);
extern void gStatGobjDispGflagSet(unsigned int *);
extern int getGameHardMode(void);
extern void isysRequestDeleteObj(int);
extern int nico_CreatePlayerGetItemObject(int, char *);

static inline char *dldResolve(unsigned int *h)
{
    int off = *h & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;

    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((*h >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

void nico_getOmakeItem(int obj, int arg)
{
    char *lay = GetLayoutClass(obj);
    char *parent = GetLayoutClass(SCRGetGetGeometryPointerLegalParentObj(lay + 0xC0));
    unsigned int *gobj = (unsigned int *)dldResolve((unsigned int *)(*(char **)(parent + 0x1A4) + 0x10));
    unsigned int *item;
    int hard;
    char *res;
    unsigned int v, *p;

    gStatGobjDispGflagSet(gobj);
    item = (unsigned int *)dldResolve(gobj);
    hard = getGameHardMode();
    if (hard != 0)
        v = item[2];
    else
        v = item[0];
    if (v != 0) {
        if (hard == 0)
            res = dldResolve(&item[1]);
        else
            res = dldResolve(&item[3]);
        D_0017AD3C = nico_CreatePlayerGetItemObject(SCRGetFirstObj(gcGlobalVar + 0x2B0), res);
    }
    _SCRStartLWS(_SCRSetupLWS(ScriptAnimationObjDef_HOME_ITEM_LIGHTNING_END, 0, *(void **)(lay + 0x134), IdentityQuaternion, arg), -1, 3, 0);
    isysRequestDeleteObj(obj);
}
