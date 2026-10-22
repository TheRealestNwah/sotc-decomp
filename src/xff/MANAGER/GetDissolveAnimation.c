extern char *GetAnimObjResource(void *);
float GetDissolveAnimation(void *object, int frame)
{
    char *resource = GetAnimObjResource(object);
    float result = 0.0f;
    if (*(short *)resource >= 10) {
        unsigned char *samples = *(unsigned char **)(resource + 0x40);
        if (samples) {
            int frames = *(short *)(resource + 4);
            if (frames != 1)
                frame -= (frames - 1) * (frame / (frames - 1));
            else frame = 0;
            result = samples[frame] * 0.0039215683937072754f;
        }
    }
    return result;
}

