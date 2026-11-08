typedef struct { char pad[0x54]; unsigned char lx; unsigned char ly; unsigned char rx; unsigned char ry; } PadStat;

#define ABS(x) ((x) < 0.0f ? -(x) : (x))
#define SGN(x) ((x) < 0.0f ? -1.0f : 1.0f)
#define AXIS(x, t, a) (ABS(x) < (t) ? 0.0f : SGN(x) * ((ABS(x) - (t)) * ((a) / ((a) - (t)))))

static inline float fsqrt(float x)
{
    float r;
    __asm__ __volatile__("sqrt.s %0, %1" : "=f"(r) : "f"(x));
    return r;
}

#define th 0.4f

void iosPadGetXZInputR(float *v, PadStat *p)
{
    float x, z, len, inv, nx, nz, ax, az, tx, tz;

    v[0] = x = p->rx * (1.0f / 127.5f) - 1.0f;
    v[1] = 0.0f;
    v[2] = z = p->ry * (1.0f / 127.5f) - 1.0f;
    v[3] = 0;
    if (x * x + z * z < th * th) {
        v[2] = v[1];
        v[0] = v[1];
        return;
    }
    len = fsqrt(x * x + z * z);
    inv = 1.0f / len;
    nz = z * inv;
    nx = x * inv;
    if (len > 1.0f) {
        v[0] = nx;
        v[2] = nz;
        return;
    }
    ax = ABS(nx);
    az = ABS(nz);
    tx = th * ax;
    tz = th * az;
    v[0] = AXIS(v[0], tx, ax);
    v[2] = AXIS(v[2], tz, az);
}
