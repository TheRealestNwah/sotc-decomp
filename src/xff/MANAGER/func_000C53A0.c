typedef struct {
    int a;
    int b;
    int c;
    int d;
} ParticleSegment;

extern ParticleSegment g_ainParticleSegment[];

static ParticleSegment *func_000C53A0(void)
{
    int i;

    for (i = 0; i < 50; i++) {
        if (g_ainParticleSegment[i].b == 0) {
            return &g_ainParticleSegment[i];
        }
    }
    return 0;
}
