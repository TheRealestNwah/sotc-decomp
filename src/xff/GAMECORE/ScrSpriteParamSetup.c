typedef struct { char c[16]; } SpriteParam;
extern void iosFree(void *);

void ScrSpriteParamSetup(SpriteParam *dst, SpriteParam *src)
{
    *dst = *src;
    iosFree(src);
}
