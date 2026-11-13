/* ~110 word diffs, same size (137 words). Static (alabel) ADPCM stream position lookup: maps o+0x278+a1 against the current segment end (res+0x10 -> +0x14); when a seek callback (o+0x7C) exists and the position crosses the boundary, it asks the callback to prefetch, advances the 5-bit slot field in the 64-bit word at o+0x38 to the next non-empty slot (12 slots at o+0xC) and resolves its entry in SH_AdpcmFileDEFAULT (20-byte records); otherwise it computes the position inside the current segment (setting bit 40 when the segment has no preload flag). Original keeps the slot counter in memory (address passed to the callback) and loads the segment pointer into different registers; ours promotes it. */
extern int DldSysUndefSymbol;
extern char SH_AdpcmFileDEFAULT[];
extern char B_0014E898[];

typedef int (*SeekFn)(unsigned int, int, void *, void *, int);

#ifdef NONMATCHING
static void func_000DB530(char *o, int a1, int *out1, int *out2, int *out3)
{
    int base = *(int *)(o + 0x278);
    SeekFn fn = *(SeekFn *)(o + 0x7C);
    char *res = *(char **)(o + 0x274);
    int pos = base + a1;
    char *ent;
    int lo;

    if (fn != 0) {
        unsigned int index = (unsigned int)(B_0014E898 - o) / 0x560u;
        int cur;
        unsigned long bits;
        char *file;
        char *e;
        int i;
        char *r;

        ent = *(char **)(res + 0x10);
        lo = *(int *)(ent + 0x14);
        if (base < lo && !(pos < lo)) {
            fn(index, lo, o + 4, &cur, *(int *)(o + 0x80));
            bits = *(unsigned long *)(o + 0x38);
            cur = (int)((bits >> 41) & 0x1F) + 1;
            for (;;) {
                if (cur >= 12) {
                    cur = 0;
                }
                if (*(int *)(o + 0xC + cur * 4) != 0) {
                    break;
                }
                cur++;
            }
            i = cur;
            *(unsigned long *)(o + 0x38) = (bits & 0xFFFFC1FFFFFFFFFFUL) | ((unsigned long)(i & 0x1F) << 41);
            file = DldSysUndefSymbol == (int)SH_AdpcmFileDEFAULT ? 0 : SH_AdpcmFileDEFAULT;
            e = *(char **)(file + 0x10) + *(int *)(o + 0xC + i * 4) * 20;
            r = *(char **)(o + 0x274);
            if (e == r) {
                *out3 = *(int *)(*(char **)(e + 0x10) + 0x10) + (pos - lo);
                *out1 = pos - *(int *)(o + 0x278);
            } else {
                *out3 = *(int *)(e + 0x10);
                *out1 = lo - *(int *)(o + 0x278);
            }
            *out2 = (int)e;
            return;
        }
    } else {
        ent = *(char **)(res + 0x10);
        lo = *(int *)(ent + 0x14);
    }
    if (base < lo && !(pos < lo)) {
        *out1 = pos - base;
        *out3 = *(int *)(ent + 0x10) + (pos - lo);
        *out2 = *(int *)(o + 0x274);
        if (*(int *)(ent + 0xC) == 0) {
            *(unsigned long *)(o + 0x38) |= 0x100000000000UL;
        }
    } else {
        *out1 = a1;
        *out2 = *(int *)(o + 0x274);
        *out3 = *(int *)(o + 0x278) + a1;
    }
}
#endif
