/* Parked draft: per-frame light list refresh on the scratchpad (0x70000000): copies the light
   manager state in, deletes lights flagged for removal, then rebuilds the global and game light
   pointer lists. Written from the m2c draft; not yet compared closely. */
#ifdef NONMATCHING
extern char B_00148CF0[];
extern int D_00136C00;
extern void ForceDelGameLighObj(int);
extern void ForceDelGlobalLighObj(int);
extern char *GetGameLightClass(int);
extern char *GetGlobalLightClass(int);
extern void iosMemToSprDmaAdrCopy(char *, int, int);
extern void iosSrpWaitDMA(void);
extern void isysGroupForExit(int, int);
extern int *isysGroupForFirst(int, int);
extern int *isysGroupForNext(int *, int);

#define SPR_FLAGS (*(unsigned int *)0x7000052C)

void LoopExecPreLightColMan(void)
{
    int n = 0;
    iosMemToSprDmaAdrCopy(B_00148CF0, 0xBD, 0x70000000);
    D_00136C00 = 0x70000000;
    iosSrpWaitDMA();
    {
        unsigned int flags = SPR_FLAGS;
        if (flags & 0xF) {
            if (flags & 0xA) {
                if (flags & 2) {
                    int m = 0;
                    int *it = isysGroupForFirst(0x7000051C, 0);
                    if (it != 0) {
                        m = *it;
                        for (;;) {
                            if (*(unsigned int *)(GetGlobalLightClass(m) + 0x110) & 0x80000)
                                ForceDelGlobalLighObj(m);
                            it = isysGroupForNext(it, 0);
                            if (it == 0)
                                break;
                            m = *it;
                        }
                    }
                    if (m != 0)
                        isysGroupForExit(m, 0);
                }
                if (SPR_FLAGS & 8) {
                    int m = 0;
                    int *it = isysGroupForFirst(0x70000528, 0);
                    if (it != 0) {
                        do {
                            m = *it;
                            if (*(unsigned int *)(GetGameLightClass(m) + 0x2C) & 0x80000)
                                ForceDelGameLighObj(m);
                            it = isysGroupForNext(it, 0);
                        } while (it != 0);
                    }
                    if (m != 0)
                        isysGroupForExit(m, 0);
                }
            }
            {
                int m = 0;
                int *it = isysGroupForFirst(0x7000051C, 0);
                char **dst = (char **)0x700005C4;
                if (it != 0) {
                    do {
                        m = *it;
                        n++;
                        *dst = GetGlobalLightClass(m);
                        dst++;
                        it = isysGroupForNext(it, 0);
                    } while (it != 0);
                }
                if (m != 0)
                    isysGroupForExit(m, 0);
                *(int *)0x70000510 = n;
            }
            {
                int m = 0;
                int *it = isysGroupForFirst(0x70000528, 0);
                int k = 0;
                char **dst = (char **)0x700007C4;
                if (it != 0) {
                    do {
                        m = *it;
                        k++;
                        *dst = GetGameLightClass(m);
                        dst++;
                        it = isysGroupForNext(it, 0);
                    } while (it != 0);
                }
                if (m != 0)
                    isysGroupForExit(m, 0);
                *(int *)0x70000520 = k;
            }
        }
    }
    SPR_FLAGS = SPR_FLAGS & ~0xFU;
}
#endif
