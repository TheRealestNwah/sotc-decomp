typedef struct {
    int a;
    int b;
    int cur;
    int end;
} SlotLfo;

typedef struct {
    int flags;
    char pad4[0x1C];
    SlotLfo pitch;
    int p30;
    char pad34[0x3C];
    int directPitch;
    char pad74[0x6C];
} Sg2Slot;

extern Sg2Slot B_000DE370[];

#ifdef NONMATCHING
/* Parked: 1 word differs (addu $t6 operands swapped: original adds $v0,$a0, gcc emits $a0,$v0); pinned locals with "+r" barriers fix everything else */
void Sg2SlotSetPitch(int s, int a, int b, int c, int d, int e)
{
    register int off __asm__("$3") = s * (int)sizeof(Sg2Slot);
    register char *bs __asm__("$2") = (char *)B_000DE370;
    register int o20 __asm__("$4") = off + 0x20;
    register Sg2Slot *p7 __asm__("$15") = (Sg2Slot *)(bs + off);
    register SlotLfo *l6 __asm__("$14") = (SlotLfo *)(bs + o20);
    __asm__("" : "+r"(p7), "+r"(l6));
    {
    register Sg2Slot *p3 __asm__("$11") = p7;
    register SlotLfo *l2 __asm__("$10") = l6;
    register SlotLfo *l4 __asm__("$4");
    register Sg2Slot *p1 __asm__("$3");
    register int div __asm__("$16");
    register int d4 __asm__("$12");
    register int d5 __asm__("$13");
    __asm__("" : "+r"(p3), "+r"(l2));
    l4 = l2;
    p1 = p3;
    __asm__("" : "+r"(l4), "+r"(p1));
    div = 12;
    d4 = 12;
    d5 = 3;
    __asm__("" : "+r"(div), "+r"(d4), "+r"(d5));
    l2->b = a;
    l4->end = b;
    l6->cur = c;
    p3->p30 = d;
    p1->directPitch = e;
    d5 = d5 / div;
    p7->flags |= 0x80;
    }
}
#endif
