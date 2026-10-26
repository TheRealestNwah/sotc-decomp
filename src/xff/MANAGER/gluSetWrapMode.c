typedef struct {
    int pad;
    union {
        long *ptr;
        char alias;
    } packet;
} GlPacket;

extern GlPacket D_00130480;
extern int iosDlGetLayer(void);
extern int glBeginWithDlLayerNo(int mode, int layer);
extern void glEnd(void);

void gluSetWrapMode(int wrapS, int wrapT)
{
    unsigned long flags;

    glBeginWithDlLayerNo(8, iosDlGetLayer());
    flags = (unsigned int)(wrapS == 0);
    if (wrapT == 0)
        flags |= 4;
    *D_00130480.packet.ptr++ = flags;
    *D_00130480.packet.ptr++ = 8;
    glEnd();
}
