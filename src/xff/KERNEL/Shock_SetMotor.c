typedef struct {
    unsigned short cur;
    unsigned short acc;
    unsigned char port;
    unsigned char val;
} ShockMotor;

/* Parked: 42 words differ (register allocation in the ramp calculation) */
#ifdef NONMATCHING
void Shock_SetMotor(unsigned char port, unsigned char level, ShockMotor *m)
{
    int val = level;
    int cur = m->cur;
    int d = val - cur;
    int out = val;
    int t;
    unsigned char o;
    unsigned int a;

    if (d > 0) {
        if (d > 0x28) {
            out = 0xFF;
        } else {
            if (val < 0x3D && cur < 0x3D) {
                if (cur < 0x33) {
                    out = 0xFF;
                    goto done;
                }
                t = (0x3C - val) * (0x3C - val) * 0xFF / 100;
            } else {
                t = d * 0xFF / 40;
            }
            if (cur < t)
                out = t;
        }
    } else if (d < 0) {
        out = 0;
        if (d >= -0x1E) {
            t = d * 0xFF / 30 + 0xFF;
            out = t < cur ? t : val;
        }
    }
done:
    o = out;
    m->acc += o;
    if ((short)m->acc > 0x40A)
        m->acc = 0x40A;
    else if ((short)m->acc < 0)
        m->acc = 0;
    a = (short)m->acc;
    m->port = port;
    m->val = o;
    m->acc = a * 3 >> 2;
    m->cur = (a << 8) / 1035;
}
#else
extern void Shock_SetMotor(unsigned char port, unsigned char level, ShockMotor *m);
#endif
