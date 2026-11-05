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
extern int InitLayoutObj(unsigned char *, int *);
static inline char *lightClass(unsigned char *object)
{
    return object[8] != 0x13 ? 0 : (char *)object + 0x20;
}
int InitLightObj(unsigned char *object, LightDefinition *definition)
{
    char *light;

    InitLayoutObj(object, (int *)definition);
    light = lightClass(object);
    *(int *)(light + 0x1C0) = definition->kind;
    ((Vec4 *)(light + 0x1D0))->q = definition->first.q;
    ((Vec4 *)(light + 0x1E0))->q = definition->second.q;
    *(float *)(light + 0x1F0) = definition->param0;
    *(float *)(light + 0x1F4) = definition->param1;
    return 1;
}
