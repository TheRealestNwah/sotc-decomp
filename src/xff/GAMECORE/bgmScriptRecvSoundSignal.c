extern int B_001888E0;

int bgmScriptRecvSoundSignal(int arg0)
{
    int temp_v1;

    temp_v1 = ((int) B_001888E0 >> arg0) & 1;
    if (temp_v1 != 0) {
        B_001888E0 ^= 1 << arg0;
    }
    return temp_v1;
}
