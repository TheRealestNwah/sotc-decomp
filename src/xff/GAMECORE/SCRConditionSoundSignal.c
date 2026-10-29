extern int bgmScriptRecvSoundSignal(int);

int SCRConditionSoundSignal(int a, int b, int c, int d)
{
    return bgmScriptRecvSoundSignal(b);
}
