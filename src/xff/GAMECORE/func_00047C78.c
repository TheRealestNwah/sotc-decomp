extern void AI_GetPosition3XYZ(float *, float *, float *, float *, float *, float *, float);
extern void AI_GetVelocity3XYZ(float *, float *, float *, float *, float *, float);

static int func_00047C78(char *ai)
{
    float *key = (float *)(ai + 0x100);

    if (key[0xA4 / 4] <= key[0xA0 / 4]) {
        AI_GetPosition3XYZ((float *)(ai + 0x180), key, (float *)(ai + 0x110), (float *)(ai + 0x120),
                           (float *)(ai + 0x150), (float *)(ai + 0x130), key[0xA4 / 4]);
        AI_GetVelocity3XYZ((float *)(ai + 0x190), key, (float *)(ai + 0x110), (float *)(ai + 0x120),
                           (float *)(ai + 0x130), key[0xA4 / 4]);
        return 1;
    }
    AI_GetPosition3XYZ((float *)(ai + 0x180), key, (float *)(ai + 0x110), (float *)(ai + 0x120),
                       (float *)(ai + 0x150), (float *)(ai + 0x130), key[0xA0 / 4]);
    AI_GetVelocity3XYZ((float *)(ai + 0x190), key, (float *)(ai + 0x110), (float *)(ai + 0x120),
                       (float *)(ai + 0x130), key[0xA0 / 4]);
    return 0;
}
