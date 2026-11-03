extern void *DldSysUndefSymbol;
extern void sndSepSetDefaultParam(void *);

typedef struct {
    int pad0;
    unsigned int ref;
    unsigned int bits;
    float vol;
} SeDef;

typedef struct {
    char pad0[0x10];
    int data;
    int a : 16;
    int b : 16;
    float vol0;
    float vol1;
    char pad20[0x24];
    SeDef *def;
} SeReq;

static inline char *resourceData(unsigned int *reference)
{
    unsigned int encoded = *reference;
    unsigned int offset = encoded & 0x3FFFF;
    char *module;
    if (offset)
        module = *(char **)((char *)reference - offset);
    else
        module = 0;
    if (module && module != DldSysUndefSymbol) {
        int index = (encoded >> 18) & 0xFFF;
        char *definition = *(char **)(module + 8);
        char *data = *(char **)(module + 0x10);
        return data + index * *(int *)(definition + 0xC);
    }
    return 0;
}

static int func_000DD938(SeReq *req)
{
    SeDef *def = req->def;
    char *res = resourceData(&def->ref);

    if (res == 0)
        return -1;
    req->data = *(int *)(res + 0x1C);
    if (req->data == 0)
        return -1;
    req->a = def->bits % 32;
    req->b = (def->bits >> 5) & 0x7F;
    req->vol1 = req->vol0 = def->vol;
    sndSepSetDefaultParam(req);
    return 0;
}
