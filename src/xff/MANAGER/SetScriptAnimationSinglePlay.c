extern void *CreateScriptAnimationSequence(void *);
extern void PlayScriptAnimationSequence(void *, int, int, int);

void *SetScriptAnimationSinglePlay(char *a)
{
    void *s = CreateScriptAnimationSequence(a);
    if (s != 0)
        PlayScriptAnimationSequence(s, *(int *)(a + 0x20), -1, 3);
    return s;
}
