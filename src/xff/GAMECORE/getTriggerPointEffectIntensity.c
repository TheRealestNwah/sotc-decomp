typedef struct {
    float intensity;
    char pad4[0x74];
} TriggerPoint;

extern TriggerPoint B_0018A9C4[];

float getTriggerPointEffectIntensity(int index)
{
    index += 3;
    return B_0018A9C4[index].intensity;
}
