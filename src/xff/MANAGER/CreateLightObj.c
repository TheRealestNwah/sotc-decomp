typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
typedef struct {
    char prefix[0x7C];
    int kind;
    Vec4 first;
    Vec4 second;
    float param0;
    float param1;
} LightDefinition;
extern int GetLayoutObjWorkSize(void *);
extern void *_isysCreateObj(void *, int, int, int, int, int);
extern int InitLayoutObj(unsigned char *, int *);
static int func_0007E1F0(unsigned char *);
static inline char *lightClass(unsigned char *object)
{
    return object[8] != 0x13 ? 0 : (char *)object + 0x20;
}
unsigned char *CreateLightObj(void *heap, int extra, LightDefinition *definition)
{
    unsigned char *object = _isysCreateObj(heap, 0x13, 0x220,
        extra + GetLayoutObjWorkSize(definition), (int)func_0007E1F0, 0x10);
    if (object) {
        char *light;
        InitLayoutObj(object, (int *)definition);
        light = lightClass(object);
        *(int *)(light + 0x1C0) = definition->kind;
        ((Vec4 *)(light + 0x1D0))->q = definition->first.q;
        ((Vec4 *)(light + 0x1E0))->q = definition->second.q;
        *(float *)(light + 0x1F0) = definition->param0;
        *(float *)(light + 0x1F4) = definition->param1;
    }
    return object;
}
