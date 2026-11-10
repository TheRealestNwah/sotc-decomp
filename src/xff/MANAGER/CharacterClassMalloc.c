#ifdef NONMATCHING
/* 4 diffs, same length (138 words): only the temp pair for the config pointer differs. Draft from the asm: carves the per-character arrays out of one iosMallocAlign block (n entries of 0x108 bytes: n * 16-byte and n * 64-byte slices, zeroing the 0x2D0 vectors with sqc2 vf0), copies three of the pointers to +0x340..0x348, then allocates the m-entry block (size depends on bit 6 of cls[0x1140]+0x38, reused in the `n` register as the Original does) and zeroes the 0x2EC / 0x2F0 vectors from ZeroPoint. Needed to get here: the n > 0 do/while with --i, reading b before a, and reusing n for the flag. The Original loads cls[0x1140] into $v0 and the flag word into $v1; ours has them swapped. Permuter (12 workers, 15 min): no improvement. */
typedef int s128 __attribute__((mode(TI)));

extern s128 ZeroPoint;
extern char *iosMallocAlign(void *, int, int);

int CharacterClassMalloc(void *ptn, char *c, int n, int m)
{
    if (n != 0) {
        char *p = iosMallocAlign(ptn, n * 0x108, 0x10);
        char *q;
        int i;

        *(char **)(c + 0x2E8) = p;
        p += n * 16;
        *(char **)(c + 0x310) = p;
        p += n * 64;
        *(char **)(c + 0x314) = p;
        p += n * 16;
        *(char **)(c + 0x2D8) = p;
        p += n * 64;
        *(char **)(c + 0x2D4) = p;
        p += n * 16;
        *(char **)(c + 0x2DC) = p;
        p += n * 16;
        *(char **)(c + 0x2E0) = p;
        p += n * 16;
        *(char **)(c + 0x318) = p;
        p += n * 16;
        *(char **)(c + 0x2D0) = p;
        p += n * 16;
        q = *(char **)(c + 0x2D0);
        if (n > 0) {
            i = n;
            do {
                __asm__ __volatile__("sqc2 $vf0, 0(%0)" : : "r"(q) : "memory");
                q += 16;
            } while (--i);
        }
        *(char **)(c + 0x328) = p;
        p += n * 16;
        *(char **)(c + 0x320) = p;
        p += n * 4;
        *(char **)(c + 0x324) = p;
    }
    *(int *)(c + 0x340) = *(int *)(c + 0x2E0);
    *(int *)(c + 0x344) = *(int *)(c + 0x310);
    *(int *)(c + 0x348) = *(int *)(c + 0x314);
    if (m != 0) {
        char *p;
        char *a;
        char *b;
        int i;

        n = (*(unsigned int *)(*(char **)(c + 0x1140) + 0x38) >> 6) & 1;
        p = iosMallocAlign(ptn, (n ? m * 47 : m * 37) * 8, 0x10);

        *(char **)(c + 0x31C) = p;
        p += m * 208;
        *(char **)(c + 0x2F4) = p;
        p += m * 16;
        *(char **)(c + 0x2F8) = p;
        p += m * 16;
        if (n) {
            *(char **)(c + 0x32C) = p;
            p += m * 80;
        } else {
            *(int *)(c + 0x32C) = 0;
        }
        *(char **)(c + 0x2F0) = p;
        p += m * 16;
        *(char **)(c + 0x2EC) = p;
        p += m * 16;
        *(char **)(c + 0x2E4) = p;
        p += m * 16;
        *(char **)(c + 0x33C) = p;
        p += m * 4;
        *(char **)(c + 0x2FC) = p;
        p += m * 3;
        *(char **)(c + 0x330) = p;
        b = *(char **)(c + 0x2EC);
        a = *(char **)(c + 0x2F0);
        for (i = m - 1; i != -1; i--) {
            __asm__ __volatile__("sqc2 $vf0, 0(%0)" : : "r"(b) : "memory");
            *(s128 *)a = ZeroPoint;
            b += 16;
            a += 16;
        }
    }
    return 1;
}
#endif
