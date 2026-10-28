typedef void (*SoundTickCallback)(void);
extern SoundTickCallback B_000C3948, B_000C394C;
extern int D_00040FB8, soundTickProcCnt;
extern void Sg2DspSetMasterVolume(int, int, int);
extern void Sg2DspSetMasterVolumeMax(void);
extern int Sg2RemoteSyncStatus(void);
extern void Sg2CtrlTickProc(void), Sg2ExPcmTickProc(void);
void tickProcSound(int muted)
{
    if (D_00040FB8 != muted) {
        if (muted) {
            Sg2DspSetMasterVolume(0, 0, 0);
            Sg2DspSetMasterVolume(1, 0, 0);
        } else {
            Sg2DspSetMasterVolumeMax();
        }
    }
    if (!muted || !D_00040FB8) {
        if (Sg2RemoteSyncStatus() == 0)
            Sg2CtrlTickProc();
        soundTickProcCnt++;
        Sg2ExPcmTickProc();
        if (B_000C394C)
            B_000C394C();
        if (B_000C3948)
            B_000C3948();
    }
    D_00040FB8 = muted;
}
