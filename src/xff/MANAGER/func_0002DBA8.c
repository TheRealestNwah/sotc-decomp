/* The unions keep the int loads of the texture header ordered after the
 * stores to the new work block, as in the Original (type-based aliasing). */
typedef struct TexWork {
    union { short s[6]; int i[3]; } h;
    int pad0C;
    int i10, i14, i18, i1C, i20, i24;
    union { char *p; int i; } object;
    char pad2C[0x14];
    union { void *p; int i; } clut[3];
} TexWork;

extern char *strchr(const char *, int);
extern void *memcpy(void *, void *, int);
extern void *iosMallocAlign(int, int, int);

static inline char *texNameInline(char *o)
{
    char *t = *(char **)(o + 0x20);
    int off = 0;
    switch (*(int *)(t + 0x1C) & 0x3F) {
    case 0x13:
    case 0x1B:
        off = 0x400;
        break;
    case 0x14:
    case 0x24:
    case 0x2C:
        off = 0x40;
        break;
    }
    return t + *(int *)(t + 0x18) + off;
}

static char *func_0002DBA8(char *object)
{
    char *texture = *(char **)(object + 0x20);
    TexWork *work;
    int i;

    if (strchr(texNameInline(object), '.') != 0)
        *strchr(texNameInline(object), '.') = 0;
    work = iosMallocAlign(*(int *)object, 0x4C, 0x10);
    work->object.p = object;
    work->i14 = 0;
    work->i10 = 0;
    work->i1C = 0;
    work->i18 = 0;
    work->i20 = 0;
    work->i24 = 0;
    work->h.s[2] = 0;
    work->h.s[0] = 0;
    work->h.s[3] = 0;
    work->h.s[1] = 0;
    work->h.s[4] = 0;
    work->h.s[5] = 0;
    switch (*(int *)(texture + 0x1C) & 0x3F) {
    case 0x13:
    case 0x1B:
        work->clut[0].p = iosMallocAlign(*(int *)object, 0x400, 0x10);
        memcpy(work->clut[0].p, texture + *(int *)(texture + 0x18), 0x400);
        for (i = 0; i < 2; i++) {
            void *p = iosMallocAlign(*(int *)object, 0x400, 0x10);
            work->clut[i + 1].p = p;
            memcpy(p, texture + *(int *)(texture + 0x18), 0x400);
        }
        break;
    case 0x14:
    case 0x24:
    case 0x2C:
        work->clut[0].p = iosMallocAlign(*(int *)object, 0x40, 0x10);
        memcpy(work->clut[0].p, texture + *(int *)(texture + 0x18), 0x40);
        for (i = 0; i < 2; i++) {
            void *p = iosMallocAlign(*(int *)object, 0x40, 0x10);
            work->clut[i + 1].p = p;
            memcpy(p, texture + *(int *)(texture + 0x18), 0x40);
        }
        break;
    default:
        for (i = 0; i < 2; i++)
            work->clut[i + 1].p = 0;
        break;
    }
    *(void **)((char *)work + 0xC) = work->clut[0].p;
    *(void **)(texture + 0xC) = work;
    return texture;
}
