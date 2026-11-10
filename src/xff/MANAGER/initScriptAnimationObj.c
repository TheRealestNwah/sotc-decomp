#ifdef NONMATCHING
/* 102 diffs (108 words vs 105). Draft from the asm: builds a 0xC0-byte creation record (SeqCreate layout like CreateScriptAnimationSequence) in a local, copies it to the outgoing by-value arg slot at sp+0 (arg declared first so it sits below c) and calls CreateScriptAnimationObj(a3, 0, rec). Args 5..9 are t0 (ptr, first word copied), t1, t2 (info block ptr), t3, and the 9th on the stack. The original reads the info fields in a first batch of loads (0x34,0xC,0x2C,0x14,0x20,4,8,0x10,0) then 0x28,0x18,0x24 after the first batch of stores; ours hoists more loads and holds one more value live (saves s0..s7+fp, frame 0x1D0 vs 0x1C0). Temporaries in load order helped (109 -> 108 words). */
typedef struct {
    int w[0x30];
} __attribute__((aligned(16))) SeqCreate;

extern void *CreateScriptAnimationObj(int, int, SeqCreate);

void *initScriptAnimationObj(int a0, int a1, int a2, int a3, int *t0, int t1, int *t2, int t3, int t4)
{
    SeqCreate arg;
    SeqCreate c;
    int l0 = *t0, l1 = t2[0xD] | 7, l2 = t2[3], l3 = t2[0xB], l4 = t2[5], l5 = t2[8], l6 = t2[1], l7 = t2[2], l8 = t2[4], l9 = l9;
    c.w[0xd] = t2[3];
    c.w[0xe] = t2[0xB];
    c.w[0xf] = t2[0xD] | 7;
    c.w[0x0] = l0;
    c.w[0x9] = l5;
    c.w[0xa] = l9;
    c.w[0xb] = l6;
    c.w[0xc] = l7;
    c.w[0x10] = l8;
    c.w[0x1] = 1;
    c.w[0x2] = 0;
    c.w[0x3] = 0;
    c.w[0x4] = 0;
    c.w[0x5] = 0;
    c.w[0x6] = 0;
    c.w[0x7] = 0;
    c.w[0x8] = 0;
    c.w[0x11] = 0;
    c.w[0x12] = 0;
    c.w[0x13] = l4;
    c.w[0x14] = t2[6];
    c.w[0x15] = t2[9];
    c.w[0x1d] = t2[10];
    c.w[0x16] = 0;
    c.w[0x17] = 0;
    c.w[0x18] = 0;
    c.w[0x19] = 0;
    c.w[0x1a] = 0;
    c.w[0x1b] = 0;
    c.w[0x1c] = 0;
    c.w[0x1e] = 0;
    c.w[0x1f] = a2;
    c.w[0x21] = 0x1000;
    c.w[0x22] = t3;
    c.w[0x24] = t4;
    c.w[0x29] = a0;
    c.w[0x2a] = a1;
    c.w[0x2b] = (int)t0;
    c.w[0x2e] = t1;
    c.w[0x2f] = 1;
    c.w[0x20] = 0;
    c.w[0x23] = 0;
    c.w[0x25] = 0;
    c.w[0x26] = 0;
    c.w[0x27] = 0;
    c.w[0x28] = 0;
    c.w[0x2c] = 1;
    c.w[0x2d] = 0;
    arg = c;
    return CreateScriptAnimationObj(a3, 0, arg);
}
#endif
