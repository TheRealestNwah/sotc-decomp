#ifdef NONMATCHING
/* 12 words off: mask lands in $a1 instead of $a0, and the shared tail uses
   bnel where the original has bnez/nop. */
extern struct { int x0; int x4; int x8; int xC; int x10; } padManagerData;
int GAMEUTIL_is_push_or_down_1p_button(int kind, int bit)
{
    int mask; int v;
    if (kind == 1) { mask = 1 << bit; v = padManagerData.x8; }
    else if (kind == 2) { mask = 1 << bit; v = padManagerData.xC; }
    else if (kind == 3) { mask = 1 << bit; v = padManagerData.x10; }
    else goto dflt;
    if (v & mask) goto one;
    return 0;
dflt:
    mask = 1 << bit;
    v = padManagerData.x0;
    if (!(v & mask)) goto zero;
one:
    return 1;
zero:
    return 0;
}
#endif
