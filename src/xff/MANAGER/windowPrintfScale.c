/* ~144 diffs, 2 words longer (179 vs 177). Window-relative scaled printf (varargs; template kPrintfScale): fades by D_00139B68[D_00139BC0] unless window flag bit 2 is set, culls when the window-relative point is outside (-16, size) (w+0x26C/0x270), formats into a stack buffer with the font board temporarily cleared, pushes layer 0x1E, sets the window colour from w+0x1F0 (4 u32 bytes /255, alpha * 1/128 * fade, + packed) and calls kPrintfScale at the point minus half the size. Remaining diffs: the Original keeps x/y in $f21/$f22 (ours $f22/$f21) and does the first pair of compares with both adds in flight; register pinning the three float args broke the va_start (155). */
typedef char *va_list;
#define va_start(ap, last)     (ap = (char *)__builtin_next_arg(last) - (__builtin_args_info(2) < 8 ? (8 - __builtin_args_info(2)) * 8 : 0))

extern float D_00139B68[];
extern int D_00139BC0;
extern int *getFontBoard(void);
extern int vsprintf(char *, const char *, va_list);
extern void iosDlPushLayer(int);
extern void iosDlPopLayer(void);
extern int kColor(int, float, float, float, float);
extern void kPrintfScale(int, int, float, const char *, ...);

#ifdef NONMATCHING
void windowPrintfScale(char *w, const char *fmt, float x, float y, float scale, ...)
{
    char buf[0x100];
    va_list ap;
    float fade;
    int *board;
    int saved;
    unsigned int *col;

    if (((int)((*(long *)(w + 0x1B8) << 30) >> 32) & 1) == 0)
        fade = D_00139B68[D_00139BC0];
    else
        fade = 1.0f;
    if (x + *(float *)(w + 0x198) > -16.0f && y + *(float *)(w + 0x19C) > -16.0f &&
        x + *(float *)(w + 0x198) < *(float *)(w + 0x26C) && y + *(float *)(w + 0x19C) < *(float *)(w + 0x270)) {
        board = getFontBoard();
        saved = *board;
        va_start(ap, scale);
        vsprintf(buf, fmt, ap);
        *board = 0;
        col = (unsigned int *)(w + 0x1F0);
        iosDlPushLayer(0x1E);
        kColor(col[4], (float)col[0] / 255.0f, (float)col[1] / 255.0f, (float)col[2] / 255.0f,
               (float)col[3] * 0.0078125f * fade);
        kPrintfScale((int)(x + *(float *)(w + 0x198) - *(float *)(w + 0x26C) * 0.5f), (int)(y + *(float *)(w + 0x19C) - *(float *)(w + 0x270) * 0.5f), scale, buf);
        iosDlPopLayer();
        *board = saved;
    }
}
#endif
