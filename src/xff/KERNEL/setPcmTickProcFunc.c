typedef void (*SoundTickCallback)(void);
extern SoundTickCallback B_000C394C;
void setPcmTickProcFunc(SoundTickCallback callback)
{
    B_000C394C = callback;
}
