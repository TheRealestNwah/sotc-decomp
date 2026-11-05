typedef struct {
    int type;
    int pad4[2];
} LwsEntry;

typedef struct {
    char pad0[0x10];
    LwsEntry *entries;
    int count;
} LwsRes;

typedef struct {
    char pad0[0x38];
    unsigned int pad38_0 : 6;
    unsigned int flag6 : 1;
    unsigned int pad38_7 : 25;
    char pad3C[0x14];
    int flags;
} LwsClass;

typedef struct {
    int pad0;
    int count4;
    char pad8[0x74];
    int res;
    char pad80[0x14];
    int n94;
    int n98;
    char pad9C[0x7C];
    LwsClass *cls;
    char pad11C[0xC];
    int n128;
    int pad12C;
    int hasE;
} LwsObj;

extern LwsRes *getAnimObjResource(int);
extern int GetLayoutObjWorkSize(LwsObj *);
extern int GetCalcNumObjWorkSize(int, int, int, int, int);

#ifdef NONMATCHING
/* 1 diff: operand order of the entries index add */
int GetLwsOrientWorkSize(LwsObj *o)
{
    LwsRes *r;
    int n;
    int i;
    int size;
    int k;
    int m;

    r = getAnimObjResource(o->res + 0x50);
    o->hasE = 0;
    n = r->count;
    for (i = 0; i < n; i++) {
        if (r->entries[i].type == 0xE) {
            o->hasE = 1;
            break;
        }
    }
    o->n128 = n;
    if (o->hasE != 0)
        o->n128 = n - 1;
    if (o->n98 != 0)
        o->count4 = n;
    size = GetLayoutObjWorkSize(o) + 0x33;
    m = o->n98;
    if (o->cls->flags & 1)
        k = o->n94 != 0 ? o->n94 * 4 : 0;
    else
        k = o->n94;
    return size + GetCalcNumObjWorkSize(n, 0, m, k, o->cls->flag6) + o->n128 * 0x50u + 0x33;
}
#endif
