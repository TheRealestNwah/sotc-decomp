typedef struct {
    int pad;
    /* The char member lets packet stores alias the pointer, so each
       increment is written back before the next store, as in the original. */
    union {
        long *ptr;
        char alias;
    } packet;
} GlPacket;

extern GlPacket D_00130480;

void glSetReg(long reg, long data)
{
    GlPacket *gl = &D_00130480;

    *gl->packet.ptr++ = data;
    *gl->packet.ptr++ = reg;
}
