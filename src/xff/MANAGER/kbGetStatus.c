typedef struct {
    unsigned int on : 1;
    unsigned int press : 1;
    unsigned int release : 1;
    unsigned int repeat : 1;
    int pad[2];
} KeyState;

typedef struct {
    KeyState key0[256];
    int count0;
    KeyState key1[256];
    KeyState key2[256];
    int count1;
    int count2;
} KbWork;

extern KbWork B_0014A6C0;


#ifdef NONMATCHING
#define CUR(i) (((KeyState *)((char *)&B_0014A6C0 + 0xC04 + B_0014A6C0.count2 * 0xC00))[i])
#define PREV(i) (((KeyState *)((char *)&B_0014A6C0 + (B_0014A6C0.count2 ? 0xC04 : 0x1804)))[i])

void kbGetStatus(KeyState *out, int *count)
{
    int i;

    *count = B_0014A6C0.count1;
    for (i = 0; i < 256; i++) {
        out[i].on = CUR(i).on;
        out[i].press = PREV(i).on ? 0 : CUR(i).on;
        out[i].release = CUR(i).on ? 0 : PREV(i).on;
    }
    B_0014A6C0.count2 ^= 1;
    for (i = 0; i < 256; i++) {
        CUR(i).on = B_0014A6C0.key0[i].on;
    }
    B_0014A6C0.count1 = B_0014A6C0.count0;
}
#else
extern void kbGetStatus(KeyState *out, int *count);
#endif
