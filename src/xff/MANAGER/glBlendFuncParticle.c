typedef struct {
    int pad;
    union {
        long *ptr;
        char alias;
    } packet;
    char pad08[0x28];
    int unknown30;
} GlPacket;

extern GlPacket D_00130480;

#define GS_SET_ALPHA(a, b, c, d, fix)                                       \
    ((unsigned long)(a) | ((unsigned long)(b) << 2) |                       \
     ((unsigned long)(c) << 4) | ((unsigned long)(d) << 6) |                \
     ((unsigned long)(fix) << 32))

void glBlendFuncParticle(int mode)
{
    unsigned int a = 0, b = 1, c = 0, d = 1, fix = 0x80;
    GlPacket *gl;

    switch (mode) {
    case 0:
        a = 0; b = 1; c = 0; d = 1;
        break;
    case 1:
        a = 0; b = 2; c = 0; d = 1;
        break;
    case 2:
        a = 2; b = 0; c = 0; d = 1;
        break;
    }
    gl = &D_00130480;
    if (gl->unknown30) {
        *gl->packet.ptr++ = GS_SET_ALPHA(a, b, c, d, fix);
        *gl->packet.ptr++ = 0x43;
    } else {
        *gl->packet.ptr++ = GS_SET_ALPHA(a, b, c, d, fix);
        *gl->packet.ptr++ = 0x42;
    }
}
