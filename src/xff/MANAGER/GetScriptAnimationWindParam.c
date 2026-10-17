typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
extern void GetGeometryPointerQuaternion(void *, char *);
extern void GetGeometryPointerPosition(void *, char *);
extern void *GetGeometryPointerObject(char *);
extern char *GetLayoutClass(unsigned char *);
int GetScriptAnimationWindParam(char *out, char *source)
{
    char *geometry = source + 0x10;
    char *layout;
    ((Vec4 *)out)->i[0] = **(signed char **)source;
    ((Vec4 *)out)->f[1] = **(float **)(source + 4);
    ((Vec4 *)out)->f[2] = **(float **)(source + 8) * 0.5f;
    ((Vec4 *)out)->f[3] = **(float **)(source + 12) * 0.5f;
    GetGeometryPointerQuaternion(out + 0x20, geometry);
    GetGeometryPointerPosition(out + 0x10, geometry);
    layout = GetLayoutClass(GetGeometryPointerObject(geometry));
    ((Vec4 *)(out + 0x30))->q = ((Vec4 *)(layout + 0x90))->q;
    return *(int *)out;
}

