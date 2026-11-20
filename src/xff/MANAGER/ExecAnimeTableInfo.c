typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; char c[16]; } Q;
extern int *DldSysUndefSymbol;
typedef struct {
    char pad[0x90];
    s128 unk90;
    char pad2[0x134 - 0xA0];
    s128 *unk134;
    int pad3;
    s128 *unk13C;
} LayoutClass;
typedef struct {
    float time;
    unsigned int ref;
} AnimeEntry;
typedef struct {
    int flag0;
    AnimeEntry *entries0;
    int flag1;
    AnimeEntry *entries1;
} AnimeTableInfo;
extern LayoutClass *GetLayoutClass(int);
extern int GetCharacterClass(int);
extern void func_000ED618(unsigned int *, int);
extern int D_00139F78;
extern int D_00139F7C;
extern int D_00139F80;
extern int D_00139F84;
extern int D_00139F88;
extern Q B_0015E420;
extern Q B_0015E430;
extern Q B_0015E440;

static inline char *resolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return t != 0 && t != DldSysUndefSymbol ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

static inline void setCurrent(int id)
{
    LayoutClass *layout = GetLayoutClass(id);
    D_00139F78 = id;
    D_00139F7C = GetCharacterClass(id);
    B_0015E430.q = *layout->unk134;
    B_0015E440.q = *layout->unk13C;
    B_0015E420.q = layout->unk90;
    D_00139F84 = id;
    D_00139F88 = 0;
    D_00139F80 = 0;
}

/* Advances both anime tables of info up to time, running each entry whose time has passed. */
void ExecAnimeTableInfo(AnimeTableInfo *info, int id, float time)
{
    AnimeEntry *p;

    if (info->flag0 != 0) {
        setCurrent(id);
        p = info->entries0;
        if (p != 0) {
            while (resolve(&p->ref) != 0) {
                if (time < p->time) {
                    info->entries0 = p;
                    goto next;
                }
                func_000ED618(&p->ref, 0);
                p++;
            }
            info->entries0 = 0;
        }
    }
next:
    if (info->flag1 != 0) {
        setCurrent(id);
        p = info->entries1;
        if (p != 0) {
            while (resolve(&p->ref) != 0) {
                if (time < p->time) {
                    info->entries1 = p;
                    return;
                }
                func_000ED618(&p->ref, 0);
                p++;
            }
            info->entries1 = 0;
        }
    }
}
