extern char B_00183EF0[];
extern char B_00183F40[];
extern char B_00183FA8[];
extern char B_00184138[];
extern char B_00184458[];
extern char *D_0017A030;
extern void *memset(void *, int, unsigned int);

static inline void gameSetF(float f)
{
    *(float *)(D_0017A030 + 0x2C) = f;
    *(float *)(D_0017A030 + 0x30) = f;
}

void gameFlagInit(void)
{
    memset(B_00183EF0, 0, 0x50);
    memset(B_00183F40, 0, 0x68);
    gameSetF(100.0f);
    memset(B_00183FA8, 0, 0x190);
    memset(B_00184138, 0, 0x320);
    memset(B_00184458, 0, 0x320);
}
