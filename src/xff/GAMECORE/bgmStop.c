typedef struct {
    char pad0[0x18];
    float fadeTime;
    char pad1C[4];
    int *done;
    unsigned int flags;
} Bgm;

void bgmStop(Bgm *bgm, int *done, float time)
{
    bgm->fadeTime = time;
    if (done != 0) {
        *done = 0;
    }
    bgm->done = done;
    bgm->flags |= 4;
}
