typedef struct { int *done; int a; int b; void (*cb)(void *); } SpriteParamEnd;

void ScrSpriteParamEnd(SpriteParamEnd *p, void *arg)
{
    if (p->done != 0)
        *p->done = 1;
    if (p->cb != 0)
        p->cb(arg);
}
