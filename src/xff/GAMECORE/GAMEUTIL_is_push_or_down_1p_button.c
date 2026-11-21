#ifdef NONMATCHING
/* 6 diffs: the mask is pinned to $a0 as in the Original; what remains is branch-likely choice in the two tests (bnel/beqz where the Original has bnez + nop and beql), which also shifts the return tail. */
extern struct { int x0; int x4; int x8; int xC; int x10; } padManagerData;
int GAMEUTIL_is_push_or_down_1p_button(int kind, int bit)
{
    register int mask __asm__("$4"); int v;
    if (kind == 1) { mask = 1 << bit; v = padManagerData.x8; }
    else if (kind == 2) { mask = 1 << bit; v = padManagerData.xC; }
    else if (kind == 3) { mask = 1 << bit; v = padManagerData.x10; }
    else goto dflt;
    v &= mask;
    if (v) goto one;
    return 0;
dflt:
    mask = 1 << bit;
    v = padManagerData.x0;
    v &= mask;
    if (!v) goto zero;
one:
    return 1;
zero:
    return 0;
}
#endif
