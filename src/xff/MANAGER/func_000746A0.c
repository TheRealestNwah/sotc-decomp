#ifdef NONMATCHING
/* 73 diffs, same length (127 words). Draft from the asm (MANAGER); the layoutClass switch is copied from CallLayoutObjDebugResetFunc (the jump table is the same RO table). Allocates a 0x290 block into lc+0x144 and a double-buffered model matrix area (2 x size, size = ((n << 2) + (n >> 6)) * 16 + 0x20), links the two 0x110-byte entries, calls modelSetMatrixTransTag for each, then modelInitDispModelClass and wires the shadow (p[4]) or clears it. Differences: the Original sets the loop counter ($s2 = 1) in the delay slot of the first iosMallocAlign and runs both loops with separate offset accumulators ($a3 / $s1) and bgez counters; ours is scheduled around different temps from the for loops. A do/while rewrite with explicit offsets made it worse (104). */
extern char *GetScriptLayoutClass(void *);
extern void *dynamic_cast_to_camera_obj(void *);
extern char *get_camera_obj_layout_class(void *);
extern char *GetLightClass(void *);

static inline char *layoutClass(unsigned char *o)
{
    switch (o[8]) {
    case 0xA:
        return (char *)o + 0x20;
    case 0xB:
        return GetScriptLayoutClass(o) + 0x70;
    case 0x11:
        return get_camera_obj_layout_class(dynamic_cast_to_camera_obj(o));
    case 0x13:
        return GetLightClass(o);
    case 9:
    case 0xD:
    case 0x16:
        return (char *)o + 0x90;
    default:
        return 0;
    }
}

extern char *iosMallocAlign(void *, int, int);
extern char *GetCharacterClass(void *);
extern void modelSetMatrixTransTag(int, char *, int, int);
extern void modelInitDispModelClass(void *, char *, int *, int, int);
extern float GetShadowLength(int);
extern unsigned short D_00136BE0;

void func_000746A0(unsigned char *o, int *p)
{
    char *lc = layoutClass(o);
    void *mem = *(void **)o;
    char *buf;
    char *m;
    int s3;
    int size;
    int has;
    int i;
    int k;
    int *sh;

    if (p[2] == 0) {
        *(char **)(lc + 0x144) = 0;
        return;
    }
    buf = iosMallocAlign(mem, 0x290, 0x10);
    *(char **)(lc + 0x144) = buf;
    has = GetCharacterClass(o) != 0;
    s3 = p[1];
    size = ((s3 << 2) + (s3 >> 6)) * 16 + 0x20;
    m = iosMallocAlign(mem, size * 2, 0x10);
    *(unsigned short *)(*(char **)(lc + 0x144) + 0x262) = D_00136BE0++;
    for (i = 0; i <= 1; i++) {
        *(char **)(*(char **)(lc + 0x144) + i * 0x110 + 0x110) = m;
        m += size;
    }
    for (k = 0; k <= 1; k++) {
        char *e = *(char **)(lc + 0x144) + k * 0x110 + 0x110;

        *(int *)(e + 4) = *(int *)e + 0x10;
        modelSetMatrixTransTag(*(unsigned short *)(*(char **)(lc + 0x144) + 0x262), *(char **)(*(char **)(lc + 0x144) + k * 0x110 + 0x110), s3, has);
    }
    modelInitDispModelClass(mem, *(char **)(lc + 0x144), (int *)p[2], *(int *)(p[2] + 0x20), p[1]);
    sh = (int *)p[4];
    if (sh != 0) {
        *(int **)(*(char **)(lc + 0x144) + 0x280) = sh;
        *(float *)(*(char **)(lc + 0x144) + 0x288) = GetShadowLength(*(int *)(*(char **)(*(char **)(lc + 0x144) + 0x280) + 0x20));
    } else {
        *(int *)(*(char **)(lc + 0x144) + 0x280) = 0;
        *(int *)(*(char **)(lc + 0x144) + 0x288) = 0;
    }
    *(float *)(*(char **)(lc + 0x144) + 0x28C) = 1.0f;
}
#endif
