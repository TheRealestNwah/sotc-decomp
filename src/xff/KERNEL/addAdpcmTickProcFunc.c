typedef void (*SoundTickCallback)(void);
extern SoundTickCallback B_000C3948;
void addAdpcmTickProcFunc(SoundTickCallback callback)
{
    B_000C3948 = callback;
}
