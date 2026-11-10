#ifdef NONMATCHING
/* Parked: 4 words differ (epilogue scheduling of the final store) */
extern char *D_00040AE0;
extern char *D_00040AE4;
extern int D_00040AE8;
extern char *B_00064C08[];
extern void iosDlPushLayer(int);
extern void iosDlChainTailCurrent(char *);
extern void iosDlPopLayer(void);

static inline void iosPushDC(char *dc)
{
    B_00064C08[D_00040AE8] = dc;
    D_00040AE8++;
    iosDlChainTailCurrent(dc);
}

void iosResetDC(char *dc)
{
    D_00040AE4 = dc;
    D_00040AE8 = 0;
    iosDlPushLayer(0);
    if (*(int *)(dc + 0x170) & 1) {
        iosPushDC(dc);
        if (*(int *)(dc + 0x170) & 1)
            iosDlChainTailCurrent(dc + 0xD0);
    } else {
        iosPushDC(dc);
    }
    D_00040AE0 = dc;
    iosDlPopLayer();
}
#endif
