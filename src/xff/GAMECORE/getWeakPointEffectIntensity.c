typedef struct { float v; char pad[0x74]; } W;
extern W B_0018A9C4[];

float getWeakPointEffectIntensity(int i)
{
    return B_0018A9C4[i].v;
}
