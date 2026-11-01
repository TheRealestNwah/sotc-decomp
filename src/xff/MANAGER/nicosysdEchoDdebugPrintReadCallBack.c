typedef struct { char pad[8]; int size; } ReadPacket;
extern int D_00139EF0;
extern char B_001502F8[];
extern char D_00141960[];
extern char D_00141990[];
extern int func_000DEE30(int, int, int);
extern void iosJumpRecoverPoint(const char *, ...);
extern void dbgPrintf(const char *, ...);

static inline int receive(int reader, char *buffer, int size)
{
    if (D_00139EF0 == 0)
        return 0;
    return func_000DEE30(reader, (int)buffer, size);
}

void nicosysdEchoDdebugPrintReadCallBack(int reader, ReadPacket *packet)
{
    if (D_00139EF0) {
        int remaining = packet->size;
        while (remaining > 0) {
            int chunk = remaining > 1000 ? 1000 : remaining;
            if (receive(reader, B_001502F8, chunk))
                iosJumpRecoverPoint(D_00141960);
            B_001502F8[chunk] = 0;
            dbgPrintf(D_00141990, B_001502F8);
            remaining -= chunk;
        }
    }
}
