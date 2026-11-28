#ifdef NONMATCHING
/* 32 diffs, same length (124 words). Walks the parts of one SpriteMenu sub-record and fills each part from the save-slot block at base + 0x110 + idx * 152. Strings SP_FILE_NAME_child1/3/4/5 (rodata order: 3, 1, 4, 5); child3 shows slot+0x11C/0x13C or -1 (format 0), child1 the +0x30 value (format 2), child4 the +0x34 value + 1 clamped to 0..99 (format 0 below 2, else 2), and child5 a 1.0f/0.0f scale from +0x3C on parts without flag 0x40. An early return plus do-while puts the slot computation after the empty-loop guard like the Original, and child4 needs a second variable for the clamped count (99 -> 35). Remaining: the Original keeps idx * 19 in $s6 and recomputes << 3 for child3 (with a pointer copy before the 0x13C load), where ours keeps idx * 152 in $fp; the loop counter and offset registers swap with it. */
extern int MakeStrHashValue(char *);
extern void SpriteMenuSetNumPartsFormatByPartsParam(void *, void *, int);

typedef struct {
    char pad[152];
} Slot;

void func_00065C70(void *menu, int *sub, char *base, int idx)
{
    char *part = (char *)sub[1] + sub[3] * 0x44;
    char *slot;
    int j;
    int off = 0;

    if (((*(unsigned int *)(part + 8) >> 4) & 0x3FF) == 0)
        return;
    slot = (char *)&((Slot *)(base + 0x110))[idx];
    j = 0;
    do {
        char *e = *(char **)(part + 4) + off;
        int *o = *(int **)e;

        if (*(unsigned int *)((char *)o + 0x10) & 0x40) {
            if (o[1] == MakeStrHashValue("SP_FILE_NAME_child3")) {
                char *b = (char *)&((Slot *)base)[idx];

                if ((*(int *)(b + 0x11C) ^ 1) != 0)
                    o[3] = -1;
                else
                    o[3] = *(int *)(b + 0x13C);
                SpriteMenuSetNumPartsFormatByPartsParam(menu, e, 0);
            }
            if (o[1] == MakeStrHashValue("SP_FILE_NAME_child1")) {
                o[3] = *(int *)(slot + 0x30);
                SpriteMenuSetNumPartsFormatByPartsParam(menu, e, 2);
            }
            if (o[1] == MakeStrHashValue("SP_FILE_NAME_child4")) {
                int v = *(int *)(slot + 0x34) + 1;

                int n;

                if (v < 0)
                    v = 0;
                o[3] = v;
                n = v;
                if (n >= 100) {
                    o[3] = 99;
                    n = 99;
                }
                SpriteMenuSetNumPartsFormatByPartsParam(menu, e, n < 2 ? 0 : 2);
            }
        } else if (o[1] == MakeStrHashValue("SP_FILE_NAME_child5")) {
            *(float *)(e + 0x14) = *(int *)(slot + 0x3C) != 0 ? 1.0f : 0.0f;
        }
        j++;
        off += 0x1C;
    } while (j < (int)((*(unsigned int *)(part + 8) >> 4) & 0x3FF));
}
#endif
