extern char gcGlobalVar[];
extern char B_001A03E0[];
extern char B_001A57E8[];
extern int SCRGetFirstObj(void *);
extern int GetCharacterClass(int);
extern void **isysGroupForFirst(void *, int);
extern void **isysGroupForNext(void **, int);
extern void isysGroupForExit(void *, int);

typedef struct {
    int v[9];
} PathPoint;

/* Parked: 15 diffs. Original keeps the loop index i separate from the gcGlobalVar+0x2EC address (no strength reduction into a pointer). */
#ifdef NONMATCHING
void updatePathInfo(void)
{
    int first;
    int i;
    char *e;
    char *w;
    int off;
    void **it;
    char *obj;

    first = SCRGetFirstObj(gcGlobalVar + 0x2B0);
    w = B_001A03E0;
    __asm__("" : "+r"(w));
    *(int *)(w + 0x5668) = first;
    if (first != 0) {
        *(int *)(w + 0x566C) = GetCharacterClass(first);
    } else {
        *(int *)(w + 0x566C) = 0;
    }
    off = 0;
    i = 0;
    do {
        e = off + B_001A57E8;
        *(int *)(e + 0x90) = 0;
        *(int *)(e + 0x94) = 0;
        obj = 0;
        it = isysGroupForFirst(gcGlobalVar + 0x2EC + i * 4, 0);
        if (it != 0) {
            do {
                PathPoint *pt;
                int *cnt;

                obj = *it;
                pt = (PathPoint *)(e + *(int *)(e + 0x90) * 0x24);
                pt->v[0] = *(int *)(obj + 0x38);
                cnt = *(int **)(obj + 0x3C);
                pt->v[1] = (int)cnt;
                pt->v[2] = *(int *)(obj + 0x40);
                pt->v[3] = *(int *)(obj + 0x44);
                pt->v[4] = *(int *)(obj + 0x48);
                pt->v[5] = *(int *)(obj + 0x4C);
                pt->v[6] = *(int *)(obj + 0x50);
                pt->v[7] = *(int *)(obj + 0x54);
                pt->v[8] = *(int *)(obj + 0x58);
                if (cnt != 0) {
                    *(int *)(e + 0x94) = *(int *)(e + 0x94) + *cnt;
                }
                *(int *)(e + 0x90) = *(int *)(e + 0x90) + 1;
                it = isysGroupForNext(it, 0);
            } while (it != 0);
        }
        if (obj != 0) {
            isysGroupForExit(obj, 0);
        }
        i++;
        off += 0x98;
    } while (i < 4);
}
#else
extern void updatePathInfo(void);
#endif
