typedef int s128 __attribute__((mode(TI)));
typedef struct Obj {
    char pad0[0x64];
    int type;
    float in[3];
    float out[3];
} Obj;
typedef struct Slot {
    Obj *obj;
    char pad4[0x4C];
    char geo[0x40];
    s128 pos;
} Slot;
typedef struct Color {
    float r, g, b, a;
} __attribute__((aligned(8))) Color;

extern void GetGeometryPointerQuaternion(float *, void *);
/* The int mode argument is declared last: under EABI it still goes in a3
   (floats use f12-f14), but loading it last lets gcc cross-jump the type 1
   call's tail into the type 2 call, as the original does. */
extern void DEBUG_disp_sphere_object(void *, void *, void *, float, float, float, int);
extern void DEBUG_disp_box_object(void *, void *, void *, float, float, float, int);

static void func_000E6100(Slot *s)
{
    Obj *o = s->obj;
    int on;
    Color red, blue;
    union { s128 q; float f[4]; } pos;
    float q[4] __attribute__((aligned(16)));

    if (o == 0) {
        return;
    }
    on = 0;
    if (o->type != 0) {
        on = 1;
        if (!(o->in[0] >= 0.0f)) {
            on = 0;
        }
    }
    if (on != 1) {
        return;
    }
    {
        static const Color r = { 1.0f, 0.0999999940395355224609375f, 0.0999999940395355224609375f, 1.0f };
        static const Color b = { 0.0999999940395355224609375f, 0.0999999940395355224609375f, 1.0f, 1.0f };
        red = r;
        blue = b;
    }
    GetGeometryPointerQuaternion(q, s->geo);
    pos.q = s->pos;
    switch (o->type) {
    case 1: {
        void *p = &pos;
        DEBUG_disp_sphere_object(p, q, &red, o->in[0], o->in[0], o->in[0], 1);
        DEBUG_disp_sphere_object(p, q, &blue, o->out[0], o->out[0], o->out[0], 1);
        break;
    }
    case 2: {
        void *p = &pos;
        DEBUG_disp_sphere_object(p, q, &red, o->in[0], o->in[1], o->in[2], 1);
        DEBUG_disp_sphere_object(p, q, &blue, o->out[0], o->out[1], o->out[2], 1);
        break;
    }
    case 3: {
        void *p = &pos;
        DEBUG_disp_box_object(p, q, &red, o->in[0], o->in[1], o->in[2], 1);
        DEBUG_disp_box_object(p, q, &blue, o->out[0], o->out[1], o->out[2], 1);
        break;
    }
    }
}
