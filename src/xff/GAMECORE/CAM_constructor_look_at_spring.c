typedef struct { float f[4]; } __attribute__((aligned(8))) V4;
static const V4 RO_00181070 = { { 2.0f, 2.0f, 2.0f, 0.0f } };
extern void constructor_double_spring_interp_cntrl3D(char *, float, float);
extern void reset_double_spring_interp_cntrl3D(char *, V4 *);

void CAM_constructor_look_at_spring(char *c)
{
    V4 v = RO_00181070;
    constructor_double_spring_interp_cntrl3D(c, 0.001f, 0.0f);
    constructor_double_spring_interp_cntrl3D(c + 0x40, 0.001f, 0.0f);
    reset_double_spring_interp_cntrl3D(c + 0x40, &v);
}
