extern volatile long gpfinishctr;
extern void scrRun(void);

#ifdef NONMATCHING
/* Parked: 4 words differ. The Original uses a plain beqz with the epilogue `ld $s0` in the delay slot and keeps the
   target in $v1 until the loop preheader copies it to $s0; gcc emits beql and uses $s0 from the start. */
void st_WaitGPFinish(int n)
{
    long target = n + gpfinishctr;

    if (gpfinishctr < target) {
        do {
            scrRun();
        } while (gpfinishctr < target);
    }
}
#else
void st_WaitGPFinish(int n);
#endif
