typedef struct {
    char unknown00[8];
    unsigned int unknown08_0 : 28;
    unsigned int underWater : 1;
    unsigned int unknown08_29 : 3;
} SoundSource;

typedef struct {
    char unknown00[8];
    unsigned long unknown08_0 : 37;
    unsigned int followGeometry : 1;
    unsigned long unknown08_38 : 26;
    char unknown10[8];
    float volume;
    float currentVolume;
    char unknown20[0x24];
    SoundSource *source;
    void *geometry;
    char unknown4C[4];
    char position[0x10];
} Sound3D;

extern void testGetCamPos(void *, void *);
extern void GetGeometryPointerPosition(void *, void *);
extern int *getFogUnderWater(void);
extern void sound3DCalc(Sound3D *, void *, void *, void *);

static inline void update(Sound3D *sound)
{
    float camPos[4];
    float camMtx[4][4];
    void *geometry = sound->geometry;
    SoundSource *source = sound->source;
    float volume;

    testGetCamPos(camPos, camMtx);
    if (sound->followGeometry)
        GetGeometryPointerPosition(sound->position, geometry);
    if (!source->underWater) {
        volume = sound->volume;
        sound->currentVolume = *getFogUnderWater() ? volume * 0.6f : volume;
    } else {
        if (!*getFogUnderWater())
            sound->currentVolume = 0;
        else
            sound->currentVolume = sound->volume;
    }
    sound3DCalc(sound, sound->position, camPos, camMtx);
}

static int func_000DDA00(Sound3D *sound)
{
    float camPos[4];
    float camMtx[4][4];
    void *geometry = sound->geometry;
    SoundSource *source = sound->source;
    float volume;

    testGetCamPos(camPos, camMtx);
    if (sound->followGeometry)
        GetGeometryPointerPosition(sound->position, geometry);
    if (!source->underWater) {
        volume = sound->volume;
        sound->currentVolume = *getFogUnderWater() ? volume * 0.6f : volume;
    } else {
        if (!*getFogUnderWater())
            sound->currentVolume = 0;
        else
            sound->currentVolume = sound->volume;
    }
    sound3DCalc(sound, sound->position, camPos, camMtx);
    return 3;
}

static int func_000DDB08(Sound3D *sound)
{
    update(sound);
    return 0;
}

static int func_000DDC08(Sound3D *sound)
{
    update(sound);
    sound->followGeometry = 0;
    return 0;
}
