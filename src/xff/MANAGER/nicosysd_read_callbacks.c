typedef struct { char pad[8]; int size; } ReadPacket;
extern int D_00139EF0;
extern char B_001502F8[];
extern int func_000DEE30(int, int, int);
extern void iosJumpRecoverPoint(const char *);
static inline int receive(int reader, char *buffer, int size)
{
    if (D_00139EF0 == 0)
        return 0;
    return func_000DEE30(reader, (int)buffer, size);
}
void nicosysdDummyReadCallBack(int reader, ReadPacket *packet)
{
    if (D_00139EF0) {
        int remaining = packet->size;
        while (remaining > 0) {
            int chunk = remaining > 1000 ? 1000 : remaining;
            if (receive(reader, B_001502F8, chunk))
                iosJumpRecoverPoint("nicosysdEchoRead:fifo packet recv data error\n");
            remaining -= chunk;
        }
    }
}
void nicosysdEchoReadCallBack(int reader, ReadPacket *packet)
{
    if (D_00139EF0) {
        int remaining = packet->size;
        while (remaining > 0) {
            int chunk = remaining > 1000 ? 1000 : remaining;
            if (receive(reader, B_001502F8, chunk))
                iosJumpRecoverPoint("nicosysdEchoRead:fifo packet recv data error\n");
            B_001502F8[chunk] = 0;
            remaining -= chunk;
        }
    }
}
void nicosysdForceEchoReadCallBack(int reader, ReadPacket *packet)
{
    if (D_00139EF0) {
        int remaining = packet->size;
        while (remaining > 0) {
            int chunk = remaining > 1000 ? 1000 : remaining;
            if (receive(reader, B_001502F8, chunk))
                iosJumpRecoverPoint("nicosysdEchoRead:fifo packet recv data error\n");
            B_001502F8[chunk] = 0;
            remaining -= chunk;
        }
    }
}
