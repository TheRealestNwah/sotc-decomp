extern int B_001888E0;

void bgmScriptSendSoundSignal(int arg0)
{
    B_001888E0 |= 1 << arg0;
}
