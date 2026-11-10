/* ~128 diffs, same length (147 words). Builds the nearest-candidate list for an interaction query: for each of the 0x50 objects in B_00149AB0 with state (+0xA0) == 1 it gets a distance via func_000CBC28 / func_000CBD28 / func_000CBDE0 (by type at +0), and if > 0 inserts {index, distance, extra float, quad} into B_00149CC0 (32-byte records) sorted by the key at (*(int **)(obj + 4))[0] (descending; the -100000 key replaces the whole list and returns 1). Returns the count. Remaining diffs: the original keeps the loop counter in $s2 with the table bases in $s3/$s6 and a lui-hi base in $s7 (the first table[0].idx load uses %lo(B_00149CC0)($s7), i.e. the insert scan is peeled for its first element), ours keeps an extra $fp. */
typedef int s128 __attribute__((mode(TI)));

typedef struct {
    int idx;
    float dist;
    float extra;
    int pad;
    s128 quad;
} Cand;

extern char *B_00149AB0[0x50];
extern Cand B_00149CC0[];
extern float func_000CBC28(void *, void *, void *, char *);
extern float func_000CBD28(void *, void *, void *, char *);
extern float func_000CBDE0(void *, void *, void *, char *);

static inline int keyOf(int idx)
{
    return **(int **)(B_00149AB0[idx] + 4);
}

#ifdef NONMATCHING
static int func_000CACE8(void *ctx)
{
    int count = 0;
    int i;

    for (i = 0; i < 0x50; i++) {
        char *o = B_00149AB0[i];
        struct { s128 quad; float extra; } L;
        float dist;

        if (o == 0)
            continue;
        if (*(int *)(o + 0xA0) != 1)
            continue;
        {
            int type = *(int *)o;

            if (type == 0)
                dist = func_000CBC28(&L.extra, &L.quad, ctx, o);
            else if (type == 1)
                dist = func_000CBD28(&L.extra, &L.quad, ctx, o);
            else
                dist = func_000CBDE0(&L.extra, &L.quad, ctx, o);
        }
        if (0.0f < dist) {
            int key = **(int **)(o + 4);
            int pos;
            int j;

            if (key == -100000) {
                count = 1;
                B_00149CC0[0].idx = i;
                B_00149CC0[0].quad = L.quad;
                B_00149CC0[0].dist = dist;
                B_00149CC0[0].extra = L.extra;
                return count;
            }
            pos = -1;
            for (j = 0; j < count; j++) {
                if (keyOf(B_00149CC0[j].idx) < key) {
                    pos = j;
                    break;
                }
            }
            if (pos == -1) {
                pos = count;
            } else {
                for (j = count - 1; j >= pos; j--)
                    B_00149CC0[j + 1] = B_00149CC0[j];
            }
            count++;
            B_00149CC0[pos].dist = dist;
            B_00149CC0[pos].quad = L.quad;
            B_00149CC0[pos].extra = L.extra;
            B_00149CC0[pos].idx = i;
        }
    }
    return count;
}
#endif
