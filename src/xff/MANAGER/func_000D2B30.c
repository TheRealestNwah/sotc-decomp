/* ~6 diffs (5 are relocation addends; the one real diff is the load order of pos[0] vs the 2.0/43.0/1.0 constants in the final column/row conversion: the Original loads pos[0] after the 2.0 constant and before 43.0). Name-entry style grid cursor handler (3 columns x 5 rows, cell 43 x 18, origin (22, 29)): positions the window cursor from the stored cell on first entry, closes the window on the 0x40040 buttons, moves the cell on dpad bits 0x2000/0x8000 (columns, wrapping 3) and 0x1000/0x4000 (rows, wrapping 5), then recomputes the cell from the cursor position. Permuter (6 workers, 7 min): 27705 -> 26750, no zero; expression/temp reorderings tried by hand (row first, temps, early loads) kept 6. */
typedef struct { int col; int row; int pad8; int init; } Sel;
extern Sel B_0014E870;
extern int padManagerData[];
extern void windowGetCursorPosOnWindow(int, float *);
extern void windowSetCursorPosOnWindow(int, float *);
extern void windowCloseRequest(void *);

#ifdef NONMATCHING
static void func_000D2B30(int unused, char *w)
{
    float pos[2];

    windowGetCursorPosOnWindow(*(int *)(w + 0x94), pos);
    if (B_0014E870.init == 0) {
        B_0014E870.init = 1;
        pos[0] = (float)(B_0014E870.col * 0x2B + 0x16);
        pos[1] = (float)(B_0014E870.row * 0x12 + 0x1D);
        windowSetCursorPosOnWindow(*(int *)(w + 0x94), pos);
    } else if ((*(int *)(w + 0x1C4) & 0x40040) != 0) {
        windowCloseRequest(w);
        **(char **)(w + 0x3E8) = 0;
    } else {
        if (padManagerData[4] & 0x2000) {
            if (++B_0014E870.col >= 3)
                B_0014E870.col = 0;
            pos[0] = (float)(B_0014E870.col * 0x2B + 0x16);
            windowSetCursorPosOnWindow(*(int *)(w + 0x94), pos);
        } else if (padManagerData[4] & 0x8000) {
            if (--B_0014E870.col < 0)
                B_0014E870.col = 2;
            pos[0] = (float)(B_0014E870.col * 0x2B + 0x16);
            windowSetCursorPosOnWindow(*(int *)(w + 0x94), pos);
        }
        if (padManagerData[4] & 0x1000) {
            if (--B_0014E870.row < 0)
                B_0014E870.row = 4;
            pos[1] = (float)(B_0014E870.row * 0x12 + 0x1D);
            windowSetCursorPosOnWindow(*(int *)(w + 0x94), pos);
        } else if (padManagerData[4] & 0x4000) {
            if (++B_0014E870.row >= 5)
                B_0014E870.row = 0;
            pos[1] = (float)(B_0014E870.row * 0x12 + 0x1D);
            windowSetCursorPosOnWindow(*(int *)(w + 0x94), pos);
        }
    }
    B_0014E870.col = (int)((pos[0] - 1.0f - 21.0f) / 43.0f);
    B_0014E870.row = (int)((pos[1] - 2.0f - 9.0f) / 18.0f - 1.0f);
}
#endif
