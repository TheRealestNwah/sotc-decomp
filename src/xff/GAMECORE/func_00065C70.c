#ifdef NONMATCHING
/* 99 diffs, same length (124 words). Draft from the asm: walks the parts of one SpriteMenu sub-record and fills each part from the save-slot block at base + 0x110 + idx * 152. Strings SP_FILE_NAME_child1/3/4/5 (rodata order: 3, 1, 4, 5); child3 shows slot+0x11C/0x13C or -1 (format 0), child1 the +0x30 value (format 2), child4 the +0x34 value + 1 clamped to 0..99 (format 0 below 2, else 2), and child5 a 1.0f/0.0f scale from +0x3C on parts without flag 0x40. Differences: the Original computes idx * 19 into a persistent register ($s6) after the empty-loop guard and builds the slot pointer there; ours hoists it into the prologue, which shifts register use. Permuter (10 workers, 20 min): best 1240. */
extern int MakeStrHashValue(char *);
extern void SpriteMenuSetNumPartsFormatByPartsParam(void *, void *, int);

void func_00065C70(void *menu, int *sub, char *base, int idx)
{
    char *part = (char *)sub[1] + sub[3] * 0x44;
    char *slot = base + 0x110 + idx * 19 * 8;
    int j;
    int off = 0;

    for (j = 0; j < (int)((*(unsigned int *)(part + 8) >> 4) & 0x3FF); j++, off += 0x1C) {
        char *e = *(char **)(part + 4) + off;
        int *o = *(int **)e;

        if (*(unsigned int *)((char *)o + 0x10) & 0x40) {
            if (o[1] == MakeStrHashValue("SP_FILE_NAME_child3")) {
                char *b = base + idx * 19 * 8;

                o[3] = ((*(int *)(b + 0x11C) ^ 1) != 0) ? -1 : *(int *)(b + 0x13C);
                SpriteMenuSetNumPartsFormatByPartsParam(menu, e, 0);
            }
            if (o[1] == MakeStrHashValue("SP_FILE_NAME_child1")) {
                o[3] = *(int *)(slot + 0x30);
                SpriteMenuSetNumPartsFormatByPartsParam(menu, e, 2);
            }
            if (o[1] == MakeStrHashValue("SP_FILE_NAME_child4")) {
                int v = *(int *)(slot + 0x34) + 1;

                if (v < 0)
                    v = 0;
                o[3] = v;
                if (v >= 100) {
                    v = 99;
                    o[3] = 99;
                }
                SpriteMenuSetNumPartsFormatByPartsParam(menu, e, v < 2 ? 0 : 2);
            }
        } else if (o[1] == MakeStrHashValue("SP_FILE_NAME_child5")) {
            *(float *)(e + 0x14) = *(int *)(slot + 0x3C) != 0 ? 1.0f : 0.0f;
        }
    }
}
#endif
