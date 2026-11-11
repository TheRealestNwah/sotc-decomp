/* Parked draft: two-buffer GIF display list for a small triangle fan; the vertex quadwords
   (a 0.866/-0.5 triangle, twice) are built on the stack and copied in. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef long s64;

extern char rootPtn[];
extern void *iosMallocAlign(char *, int, int);

static void *func_00019B78(s64 arg)
{
    float verts[32] __attribute__((aligned(16))) = {
        0.0f, 1.0f, 1.0f, 1.0f, -0.8660254f, -0.5f, 1.0f, 0.0f, 2.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.8660254f, 0.0f, -0.5f, 1.0f, 0.0f, 2.0f, 0.0f, 1.0f, -0.8660254f, 0.0f,
        -0.5f, 1.0f, 0.8660254f, 0.0f, -0.5f, 1.0f, 0.0f, 0.0f
    };
    char *list = iosMallocAlign(rootPtn, 0x1E0, 0x10);
    int *hdr = (int *)list;
    char **slot;
    int buf;

    hdr[2] = (int)(list + 0x20);
    hdr[0] = 0x12;
    hdr[3] = (int)(list + 0x100);
    hdr[1] = 0;
    slot = (char **)(list + 8);
    for (buf = 0; buf < 2; buf++) {
        char *p = *slot;
        s128 *dst;
        s128 *src = (s128 *)verts;
        unsigned int i;
        s64 sel = (arg << 7) | (arg != 0 ? 2 : 0x42);

        *(s64 *)(p + 0x40) = (sel << 0x2F) | ((0x10004000L << 0x20) | 0x8008);
        *(int *)(p + 0x0) = 0x6000000D;
        *(int *)(p + 0x8) = 0x10000000;
        *(int *)(p + 0xC) = 0;
        *(int *)(p + 0x10) = 0;
        *(int *)(p + 0x14) = 0;
        *(int *)(p + 0x18) = 0x01000101;
        *(int *)(p + 0x1C) = 0x6C0103A0;
        *(int *)(p + 0x28) = 4;
        *(int *)(p + 0x30) = 0;
        *(int *)(p + 0x34) = 0;
        *(int *)(p + 0x38) = 0;
        *(int *)(p + 0x3C) = 0x6C098000;
        *(s64 *)(p + 0x48) = (0xDFL << 0x20) | 4;
        *(s64 *)(p + 0x20) = (sel << 0x2F) | ((0x10004000L << 0x20) | 0x8002);
        dst = (s128 *)(p + 0x50);
        for (i = 0; i < 8; i++)
            *dst++ = *src++;
        ((int *)dst)[0] = 0x14000012;
        ((int *)dst)[1] = 0;
        ((int *)dst)[2] = 0;
        ((int *)dst)[3] = 0x10000000;
        slot += 1;
    }
    return list;
}
#endif
