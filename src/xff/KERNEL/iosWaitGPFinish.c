extern void isysSleepSubThread(void);

extern volatile long D_00040BA8;

void iosWaitGPFinish(int unused, int frames)
{
    long start = D_00040BA8;

    if (D_00040BA8 < start + frames) {
        do {
            isysSleepSubThread();
        } while (D_00040BA8 < start + frames);
    }
}
