typedef struct {
    unsigned short cur;
    unsigned short acc;
    unsigned char port;
    unsigned char val;
} ShockMotor;

void Shock_SetMotor(unsigned char port, unsigned char level, ShockMotor *m)
{
    int val = level;
    int cur = m->cur;
    int d = val - cur;
    register int out __asm__("$7") = val;
    unsigned int a;
    unsigned int c;

    if (d > 0) {
        if (d > 0x28) {
            out = 0xFF;
        } else {
            if (val < 0x3D && cur < 0x3D) {
                if (cur < 0x33) {
                    out = 0xFF;
                    goto done;
                }
                d = 0x3C - val;
                d = d * d * 0xFF / 100;
            } else {
                d = d * 0xFF / 40;
            }
            {
                register int up __asm__("$3") = cur < d;
                if (up)
                    out = d;
            }
        }
    } else if (d < 0) {
        out = 0;
        if (d >= -0x1E) {
            d = d * 0xFF / 30 + 0xFF;
            out = d < cur ? d : val;
        }
    }
done:
    level = out;
    m->acc += level;
    if ((short)m->acc > 0x40A)
        m->acc = 0x40A;
    else if ((short)m->acc < 0)
        m->acc = 0;
    a = (short)m->acc;
    c = (a << 8) / 1035;
    m->port = port;
    m->val = level;
    m->acc = a * 3 >> 2;
    m->cur = c;
}
