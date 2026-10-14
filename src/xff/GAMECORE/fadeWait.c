extern void scrRun();
extern int D_0017A020;

void fadeWait(void)
{
    if (D_0017A020 != 0) {
        do {
            scrRun();
        } while (D_0017A020 != 0);
    }
}
