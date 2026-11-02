typedef struct {
    char pad0[0x2C];
    int f2C;
    int f30;
    int f34;
    int f38;
    int f3C;
    int f40;
    int f44;
    int f48;
    int f4C;
    int f50;
    int f54;
    int f58;
    int f5C;
    int f60;
    int f64;
    int f68;
} YawPitchCntrl;

extern void func_0000DAF0(YawPitchCntrl *);

void reset_nico_yaw_pitch_cntrl(YawPitchCntrl *c)
{
    func_0000DAF0(c);
    c->f2C = 0;
    c->f30 = 0;
    c->f38 = 0;
    c->f34 = 0;
    c->f3C = 0;
    c->f40 = 0;
    c->f48 = 0;
    c->f44 = 0;
    c->f4C = 0;
    c->f50 = 0;
    c->f54 = 0;
    c->f58 = 0;
    c->f5C = 0;
    c->f60 = 0;
    c->f64 = 0;
    c->f68 = 0;
}
