/* Parked attempt: 4 words differ (+0x60, +0x64, +0x70, +0x74). gcc schedules the
   lw of D_00131C00.size before the move of the copy source, and reverses the
   bssEnd/memEnd additions; no statement order or source-pointer form fixes it. */
#ifdef NONMATCHING
struct LoaderInfo {
    int w[16];
    int size;
    int pad;
};

struct LoaderMemoryInfo {
    int memStart;
    int memEnd;
    int bssStart;
    int bssEnd;
    int heapStart;
    int heapEnd;
    int heapCurrent;
    int stackTop;
    struct LoaderInfo info;
};

extern struct LoaderInfo D_00131C00;
extern int D_00139E00;
extern int D_0013A014;

int LoaderSysGetMemoryInfo(struct LoaderMemoryInfo *m)
{
    int base;
    int baseSize;
    int bss;
    int bssSize;

    m->heapCurrent = D_00139E00;
    __asm__ volatile("lui %0, %%hi(D_1FE0000)\n\tnop\n\taddiu %0, %0, %%lo(D_1FE0000)\n\tnop" : "=r"(base));
    m->memStart = base;
    __asm__ volatile("lui %0, %%hi(D_20000)\n\tnop\n\taddiu %0, %0, %%lo(D_20000)\n\tnop" : "=r"(baseSize));
    __asm__ volatile("lui %0, %%hi(D_16A398)\n\tnop\n\taddiu %0, %0, %%lo(D_16A398)\n\tnop" : "=r"(bss));
    m->bssStart = bss;
    __asm__ volatile("lui %0, %%hi(D_40000)\n\tnop\n\taddiu %0, %0, %%lo(D_40000)\n\tnop" : "=r"(bssSize));
    m->heapEnd = D_0013A014 + D_00131C00.size;
    m->memEnd = base + baseSize;
    m->bssEnd = bss + bssSize;
    m->heapStart = D_0013A014;
    m->stackTop = base;
    m->info = D_00131C00;
    return 1;
}
#endif
