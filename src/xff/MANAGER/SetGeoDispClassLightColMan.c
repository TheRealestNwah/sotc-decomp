typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
extern char *D_00136C00;
extern void ExecGlobalLightMan(void *, void *);
extern void SetWorkFromGlobalLight(void *);
extern void ExecGameLight(void *, int, void *);
static void func_0007ACD0(void *, void *, void *);

int SetGeoDispClassLightColMan(char *object)
{
    char *work = D_00136C00;
    unsigned char side = object[0xC0] & 1;
    if (*(int *)(object + 0xEC) != 0) {
        s128 position = ((Vec4 *)(object + 0x10))->q;
        *(float *)(work + 0x10) = 0.0f;
        ((Vec4 *)work)->q = position;
        *(float *)(work + 0x14) = *(float *)(work + 0x10);
        ((Vec4 *)work)->f[3] = 1.0f;
        *(int *)(work + 0x18) = side;
        *(int *)(work + 0x530) = 0;
        ExecGlobalLightMan(work, work);
        SetWorkFromGlobalLight(work);
        ExecGameLight(work, side, work);
        func_0007ACD0(work, object, work);
    }
    return 1;
}
