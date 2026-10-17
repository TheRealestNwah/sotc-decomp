typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
extern float *GetGeometryPointerSurfacePlane(char *);
void ConvertFromCollisionPointToDynamics(char *out, char *point)
{
    Vec4 *plane;
    int *tail;
    ((Vec4 *)out)->q = ((Vec4 *)(point + 0x40))->q;
    plane = (Vec4 *)GetGeometryPointerSurfacePlane(point);
    tail = (int *)(out + 0x20);
    ((Vec4 *)(out + 0x10))->q = plane->q;

    tail[0] = *(int *)point;
    tail[1] = *(int *)(point + 4);
}

