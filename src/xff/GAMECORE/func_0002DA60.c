typedef struct {
    char pad0[0x9C];
} LightParam;

typedef struct {
    char pad0[0x10];
    LightParam *lights;
} SheetSegHeader;

typedef struct {
    char pad0[0x20];
    int light;
} LightRef;

extern SheetSegHeader *GetWorldLayoutSheetSegHeader(void);
extern void setLightParam(LightParam *);

static int func_0002DA60(LightRef *r)
{
    SheetSegHeader *h = GetWorldLayoutSheetSegHeader();

    if (h != 0)
        setLightParam(&h->lights[r->light]);
    return 0;
}
