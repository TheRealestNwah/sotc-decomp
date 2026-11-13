/* ~100 word diffs (shifted), same size (121 words). Static (alabel): spawns one 0x20-byte chip-arg script object (createScriptObj with func_00024638) per cell along an axis of the D_0017A340 grid: mode 0 iterates x (a2..a2+count) at fixed y from a3, mode 1 iterates y (a3..) at fixed x from a2. Original keeps D_0017A340 in a2/a3 (not a callee-saved copy) and computes both coordinates before the allocation; ours spends s-registers differently and reorders the divides. */
typedef struct {
    char pad00[0x28];
    int x0;
    int y0;
    char pad30[4];
    int y1;
    int divX;
    int divY;
} StageGrid;
typedef struct { int a; int b; } ChipArg;
extern StageGrid D_0017A340;
extern char gcGlobalVar[];
extern char rootPtn;
extern void func_00024638(void);
extern ChipArg *iosMallocAlign(void *, int, int);
extern int createScriptObj();

#ifdef NONMATCHING
static void func_0001ED58(int unused, int mode, int a2, int a3, int count)
{
    StageGrid *g;
    int i;
    int end;
    int fixed;
    ChipArg *o;

    switch (mode) {
    case 0:
        g = &D_0017A340;
        i = a2;
        end = i + count;
        fixed = -(g->y0 + (g->y1 - a3 / g->divY));
        for (; i < end; i++) {
            int v = g->x0 + i / g->divX;
            o = iosMallocAlign(&rootPtn, 0x20, 0x10);
            o->a = v;
            o->b = fixed;
            createScriptObj(func_00024638, o, *(int *)(gcGlobalVar + 0x308), 0x1000, 0, 1, 0, 0);
        }
        break;
    case 1:
        g = &D_0017A340;
        i = a3;
        end = i + count;
        fixed = g->x0 + a2 / g->divX;
        for (; i < end; i++) {
            int v = g->y0 + (g->y1 - i / g->divY);
            o = iosMallocAlign(&rootPtn, 0x20, 0x10);
            o->a = fixed;
            o->b = -v;
            createScriptObj(func_00024638, o, *(int *)(gcGlobalVar + 0x308), 0x1000, 0, 1, 0, 0);
        }
        break;
    }
}
#endif
