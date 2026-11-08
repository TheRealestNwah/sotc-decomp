typedef unsigned long u64;

typedef struct {
    u64 *tag;
    u64 *head;
    u64 *data;
    u64 *cur;
    char pad10[0xC];
    int err;
} GsPacket;

extern GsPacket *D_00040BF4;
extern u64 *iosGetPacketPtrPath1(void);
#ifdef NONMATCHING
/* Parked: 49 words differ (original reloads D_00040BF4 after every store; this exact body matches with -fno-strict-aliasing) */

u64 *gsRegBegin(void)
{
    D_00040BF4->err = 0;
    D_00040BF4->cur = iosGetPacketPtrPath1();
    if (D_00040BF4->cur == 0) {
        D_00040BF4->err = 1;
    } else {
        D_00040BF4->tag = D_00040BF4->cur;
        D_00040BF4->cur++;
    }
    if (D_00040BF4->err == 0) {
        D_00040BF4->head = D_00040BF4->cur;
        *D_00040BF4->cur++ = 0;
        if ((int)D_00040BF4->cur & 3)
            *D_00040BF4->cur++ = 0;
        D_00040BF4->data = D_00040BF4->cur;
        D_00040BF4->cur += 2;
    }
    return D_00040BF4->cur;
}
#endif
