extern char *GetCharacterClass(void *);
extern char *GetLayoutClass(void *);
extern int AI_CheckViewInCameraClipVolume(void *, void *);
extern void *iosgluGetCameraContext(void);
extern float GetScreenRadius(void *, void *, float);

typedef struct {
    int inView;
    float minRadius;
    float radius;
} OptSample;

static inline int isFloatVisible(OptSample *s, char *l)
{
    int buf[4];

    s->inView = AI_CheckViewInCameraClipVolume(buf, *(void **)(l + 0x134));
    if (s->inView != 0) {
        s->radius = GetScreenRadius(iosgluGetCameraContext(), *(void **)(l + 0x134), 1.0f);
        if (s->radius < s->minRadius)
            return 0;
        return 1;
    }
    return 0;
}

int AI_OptFloatFrameSample(void *obj, OptSample *s)
{
    char *c = GetCharacterClass(obj);
    char *l = GetLayoutClass(obj);

    if (isFloatVisible(s, l) == 0) {
        c[0x52B] = 0;
        c[0x53A] = 1;
        return 0;
    }
    c[0x53A] = 0;
    c[0x52B] = 1;
    return 1;
}
