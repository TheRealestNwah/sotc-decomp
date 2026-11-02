typedef unsigned long u_long;

typedef struct {
    char pad0[0x60];
    u_long xyoffset1;
    u_long xyoffset1addr;
    u_long xyoffset2;
    u_long xyoffset2addr;
    u_long scissor1;
    u_long scissor1addr;
    u_long scissor2;
    u_long scissor2addr;
    char padA0[0x174 - 0xA0];
    int x;
    int y;
    int w;
    int h;
} DispCtx;

#define SCE_GS_SET_XYOFFSET(ofx, ofy) ((u_long)(ofx) | ((u_long)(ofy) << 32))
#define SCE_GS_SET_SCISSOR(scax0, scax1, scay0, scay1) \
    ((u_long)(scax0) | ((u_long)(scax1) << 16) | ((u_long)(scay0) << 32) | ((u_long)(scay1) << 48))

void iosSetDCViewPortCenter(DispCtx *dc, int x, int y, int w, int h, int cx, int cy)
{
    dc->x = x;
    dc->y = y;
    dc->w = w;
    dc->h = h;
    dc->xyoffset1addr = 0x18;
    dc->xyoffset2addr = 0x19;
    dc->xyoffset1 = dc->xyoffset2 = SCE_GS_SET_XYOFFSET((cx + 0x800) << 4, (cy + 0x800) << 4);
    dc->scissor1addr = 0x40;
    dc->scissor2addr = 0x41;
    dc->scissor1 = dc->scissor2 = SCE_GS_SET_SCISSOR(x, x + w - 1, y, y + h - 1);
}
