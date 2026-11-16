/* Parked: 1 diff, same length (103 words, includes the func_00028020 epilogue tail). Remaining: the third loop's empty-list exit is bltzl here but bltz in the Original (both put the B_00188650 address in the delay slot). Per-iteration values must be block-scoped (`int v` inside each loop); a shared v costs 10 words, pointer loops 70+. A 25-minute permuter run found nothing better. */
#ifdef NONMATCHING
extern int D_0017A870;
extern int D_0017A874;
extern int D_0017A878;
extern int B_00188650[];
extern int B_00188668[];
extern void scrRun(void);
extern void func_00026E38(int);
extern void func_00027070(int);
extern void func_00027588(int);
extern void func_00027778(int);
extern void func_00027968(int);
extern void func_00027B70(int);

/* Waits for the stage lock, then reruns every area and part list under stage context id before restoring the previous context. */
static void func_00027EB8(int id)
{
    int i;
    int save;

    while (D_0017A870 == 0)
        scrRun();
    D_0017A870 = 0;
    D_0017A878 = 1;
    save = D_0017A874;
    D_0017A874 = id;
    for (i = 0; B_00188668[i] >= 0; i++) {
        int v = B_00188668[i];
        func_00026E38(v);
        func_00027968(v);
    }
    for (i = 0; B_00188650[i] >= 0; i++)
        func_00027588(B_00188650[i]);
    scrRun();
    D_0017A874 = save;
    for (i = 0; B_00188668[i] >= 0; i++) {
        int v = B_00188668[i];
        func_00027B70(v);
        func_00027070(v);
    }
    for (i = 0; B_00188650[i] >= 0; i++)
        func_00027778(B_00188650[i]);
    scrRun();
    D_0017A874 = id;
    D_0017A878 = 0;
    D_0017A870 = 1;
}
#endif
