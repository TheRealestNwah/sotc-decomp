typedef struct {
    int name;
    int disp;
    int pad;
    int clip;
    int light;
    int flag;
} GeoDef;
extern void *_isysCreateObj(void *, int, int, int, int, int);
extern int GetLayoutDispObjGroup(void);
extern int isysAddGroupWithLinkParam(void *, void *, int, int);
extern void InitSortObj(char *, int);
extern void isysSetObjImmediateDeleteFunc(void *, int);
extern void _isysDeleteGroup(void *, void *, int);
static void func_000724E8(void *);
static void func_000724F0(void *);
static inline char *geoClass(char *object)
{
    return (unsigned char)object[8] == 0x24 ? object + 0x20 : 0;
}
char *CreateGeoDispObj(void *heap, int extra, GeoDef *definition)
{
    char *object = _isysCreateObj(heap, 0x24, 0x110, extra + 0x1000, (int)func_000724E8, 0x10);
    if (object) {
        char *geo = geoClass(object);
        isysAddGroupWithLinkParam(object, (void *)GetLayoutDispObjGroup(), 0, 0);
        *(int *)(geo + 0xEC) = definition->name;
        *(int *)(geo + 0xD0) = definition->disp;
        *(int *)(geo + 0xD4) = definition->pad;
        *(int *)(geo + 0xD8) = definition->clip;
        *(int *)(geo + 0xE0) = definition->light;
        *(int *)(geo + 0xE8) = definition->flag;
        InitSortObj(geo, (int)object);
        isysSetObjImmediateDeleteFunc(object, (int)func_000724F0);
    }
    return object;
}
static void func_000724E8(void *unused)
{
}
static void func_000724F0(void *object)
{
    _isysDeleteGroup(object, (void *)GetLayoutDispObjGroup(), 0);
}
