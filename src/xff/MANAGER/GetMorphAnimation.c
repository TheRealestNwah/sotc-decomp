extern char *GetAnimObjResource(void *);

static inline float sampleToFloat(unsigned char *samples, int i)
{
    return samples[i] * 0.0039215683937072754f;
}

float GetMorphAnimation(void *object, float frame)
{
    char *resource = GetAnimObjResource(object);
    float result = 0.0f;
    if (*(short *)resource >= 12 && (*(unsigned short *)(resource + 2) & 2)) {
        int frames = *(short *)(resource + 4);
        int i;
        unsigned char *samples;
        float t;
        if (frames == 1)
            frame -= (int)frame;
        else
            frame -= (frames - 1) * (int)(frame / (frames - 1));
        i = (int)frame;
        samples = *(unsigned char **)(resource + 0x44);
        t = frame - i;
        {
            float a = sampleToFloat(samples, i) * (1.0f - t);
            float b = sampleToFloat(samples, i + 1) * t;
            result = b + a;
        }
    }
    return result;
}
