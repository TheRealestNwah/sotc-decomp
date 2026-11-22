/* Parked: 10 diffs (permuter found no improvement after 30 min).
 * Remaining: x and y are held in swapped callee-saved FP registers
 * ($f21/$f22), and the two va_list spills (sd $t0/$t1) are scheduled
 * after the 0x1B8 bit test instead of between its shifts.
 */
#ifdef NONMATCHING
typedef char *va_list;
#define va_start(ap, last)     (ap = (char *)__builtin_next_arg(last) - (__builtin_args_info(2) < 8 ? (8 - __builtin_args_info(2)) * 8 : 0))

extern float D_00139B68[];
extern int D_00139BC0;
extern int *getFontBoard(void);
extern int vsprintf(char *, const char *, va_list);
extern void iosDlPushLayer(int);
extern void iosDlPopLayer(void);
extern int kColor(int, float, float, float, float);
extern void kPrintf(int, int, const char *, ...);

void windowPrintf(char *w, const char *fmt, float x, float y, ...)
{
    char buf[0x100];
    va_list ap;
    float fade;
    float px, py;
    int *board;
    int saved;
    unsigned int *col;

    if (((int)((*(long *)(w + 0x1B8) << 30) >> 32) & 1) == 0)
        fade = D_00139B68[D_00139BC0];
    else
        fade = 1.0f;
    px = x + *(float *)(w + 0x198);
    py = y + *(float *)(w + 0x19C);
    if (px > -16.0f && py > -16.0f && px < *(float *)(w + 0x26C) && py < *(float *)(w + 0x270)) {
        board = getFontBoard();
        saved = *board;
        va_start(ap, y);
        vsprintf(buf, fmt, ap);
        *board = 0;
        col = (unsigned int *)(w + 0x1F0);
        iosDlPushLayer(0x1E);
        {
            float r = (float)col[0] / 255.0f;
            float g = (float)col[1] / 255.0f;
            float b = (float)col[2] / 255.0f;
            float al = (float)col[3] * 0.0078125f * fade;
            kColor(col[4], r, g, b, al);
        }
        kPrintf((int)(x + *(float *)(w + 0x198) - *(float *)(w + 0x26C) * 0.5f), (int)(y + *(float *)(w + 0x19C) - *(float *)(w + 0x270) * 0.5f), buf);
        *board = saved;
        iosDlPopLayer();
    }
}
#endif
