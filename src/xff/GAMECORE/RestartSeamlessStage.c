typedef struct { int request; int b; void *buf; } SeamlessLoad;

extern SeamlessLoad D_0017A340;

void RestartSeamlessStage(void)
{
    SeamlessLoad *s = &D_0017A340;

    if (s->buf != 0) {
        s->request = 1;
    }
}
