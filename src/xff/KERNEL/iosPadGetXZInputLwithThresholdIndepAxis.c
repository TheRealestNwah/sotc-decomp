typedef struct { char pad[0x54]; unsigned char lx; unsigned char ly; } PadStat;

#define ABS(x) ((x) < 0.0f ? -(x) : (x))
#define SGN(x) ((x) < 0.0f ? -1.0f : 1.0f)
#define AXIS(x, th) (ABS(x) < (th) ? 0.0f : SGN(x) * ((ABS(x) - (th)) * (1.0f / (1.0f - (th)))))

void iosPadGetXZInputLwithThresholdIndepAxis(float *v, PadStat *p, float th)
{
    v[0] = p->lx * (1.0f / 127.5f) - 1.0f;
    v[1] = 0.0f;
    v[2] = p->ly * (1.0f / 127.5f) - 1.0f;
    v[3] = v[1];
    v[0] = AXIS(v[0], th);
    v[2] = AXIS(v[2], th);
}
