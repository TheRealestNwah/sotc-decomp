#ifdef NONMATCHING
/* 4 diffs: original keeps frames + D_00040BA8 in $v1 and only copies it to $s0 inside the loop; gcc allocates $s0 up front. Permuter best 40 did not improve on it. */
extern void isysSleepSubThread(void);

extern volatile long D_00040BA8;

void iosWaitGPFinish(int unused, long frames)
{
    long target = D_00040BA8 + frames;

    if (D_00040BA8 < target) {
        do {
            isysSleepSubThread();
        } while (D_00040BA8 < target);
    }
}
#endif
