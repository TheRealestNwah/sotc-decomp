typedef struct { char pad[0x38]; float h; float pad3C; } Probe;

extern void CopyGeometryPointer(void *, void *);
extern void GetGeometryPointerPosition(void *, void *);
extern int IsGeoColStatus(void *, long, long);
/* Parameter order is a search result: the declared order sets the order of the argument setup instructions. */
extern int charrootdyn_detectCharClimbableWall(float, float, void *, void *, int, void *, int, float, float, int);

static int func_00090408(void *geo, char *obj, int check)
{
    char pos[0x10] __attribute__((aligned(16)));
    Probe probe __attribute__((aligned(16)));
    char hit[0x60] __attribute__((aligned(16)));
    int flag = 0;
    int s0, s2, v;

    GetGeometryPointerPosition(pos, geo);
    if (check != 0 &&
        charrootdyn_detectCharClimbableWall(1.3f, 0.55f, &probe, geo, 1, pos, *(int *)(obj + 0x134), 0.5f, 0.0f, (int)(obj + 0xE20)) != 0) {
        if (probe.h < 0.55f && IsGeoColStatus(hit, 0x7C000000L, 0x18000000L) == 0 &&
            IsGeoColStatus(hit, 0xFE00L << 38, 0x9E00L << 38) == 0) {
            CopyGeometryPointer(geo, hit);
            flag = 4;
        }
    }
    s0 = IsGeoColStatus(geo, 2, 2);
    s2 = IsGeoColStatus(geo, 4, 4);
    v = IsGeoColStatus(geo, 1, 1);
    if (s0 != 0) goto one;
    if (s2 != 0) goto two;
    if (v != 0) goto two;
one:
    flag |= 1;
    goto done;
two:
    flag |= 2;
done:
    return flag;
}
