typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
typedef struct { int *table; int index; char finder[0x14]; int enabled; } VuColiDisp;
extern VuColiDisp B_00183B30;
extern void *get_main_cameraman(void);
extern void *get_cur_camera_target(void *);
extern char *GetLayoutClass(void *);
extern void glColor4f(float, float, float, float);
extern void DebugDispRadiusIndicator(Vec4 *, float, int);
extern void GetCollisionDB(void *, int *, int, Vec4 *, Vec4 *, float);

void updateVuColiDispWork(void)
{
    void *cameraman = get_main_cameraman();
    Vec4 pos;

    if (B_00183B30.enabled == 0)
        return;
    if (get_cur_camera_target(cameraman) != 0)
        pos.q = (*(Vec4 **)(GetLayoutClass(get_cur_camera_target(cameraman)) + 0x134))->q;
    else
        __asm__ __volatile__("sqc2 vf0, 0x0(%0)" : : "r"(&pos) : "memory");
    glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
    DebugDispRadiusIndicator(&pos, 10.0f, 5);
    GetCollisionDB(B_00183B30.finder, B_00183B30.table + B_00183B30.index, 0, &pos, &pos, 10.0f);
}
