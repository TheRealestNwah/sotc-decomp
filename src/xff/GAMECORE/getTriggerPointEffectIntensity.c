typedef struct { float v; char pad[0x74]; } TP; extern TP B_0018A9C4[]; float getTriggerPointEffectIntensity(int index) { index += 3; return B_0018A9C4[index].v; }
