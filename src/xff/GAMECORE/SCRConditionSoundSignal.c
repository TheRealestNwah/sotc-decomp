extern int bgmScriptRecvSoundSignal();

int SCRConditionSoundSignal(int a, int b, int c, int d)
{
    return bgmScriptRecvSoundSignal(b, b, c, d);
}
