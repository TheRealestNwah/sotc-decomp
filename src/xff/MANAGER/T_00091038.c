extern void FlushScriptLayoutObj(void *);
extern void FlushJudgeVolumeClass(void *);
extern void isysFlushISYSLetterObj(void *);

static void T_00091038(char *o)
{
    char *w = *(unsigned char *)(o + 8) == 0xD ? o + 0x20 : 0;

    FlushScriptLayoutObj(o);
    if (*(void **)(w + 0x33C)) {
        FlushJudgeVolumeClass(*(void **)(w + 0x33C));
        *(void **)(w + 0x33C) = 0;
    }
    isysFlushISYSLetterObj(o);
}
