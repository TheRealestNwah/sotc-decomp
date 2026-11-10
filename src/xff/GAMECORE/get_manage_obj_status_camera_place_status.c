#ifdef NONMATCHING
/* 131 diffs, 3 words short (160 vs 163). Draft from the asm; dld helpers from func_000AE758. Finds the camera-place entry (0x18-byte records: two dld refs, a frame range lo/hi and the status value at +0x14) of a managed object whose motion kind (cc+0x750) and sub-kind (cc+0x578) match and whose range contains the current animation frame, returning its status or 0. The Original keeps the character class in $a2 and re-loads *(layout+0x1A8) for each of the two dld refs (count at +0xC, data at +0x10, not CSE-d); ours keeps cc in $a0 and loads the pointer once, which shifts the first branches and everything after. */
extern int *DldSysUndefSymbol;

static inline char *dldBase(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return t != 0 && t != DldSysUndefSymbol ? (char *)t[4] : 0;
}

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    if (t != 0 && t != DldSysUndefSymbol)
        return (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3];
    return 0;
}

static inline int dldCount(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return t != 0 && t != DldSysUndefSymbol ? t[3] : 0;
}

extern char *GetLayoutClass(void *);
extern char *GetCharacterClass(void *);
extern float GetCharacterClassCurAnimationCurFrame(void *);

int get_manage_obj_status_camera_place_status(char *obj)
{
    char *found = 0;
    char *lc;
    char *cc;
    int s3;
    int s2;

    if (*(void **)(obj + 8) != 0) {
        lc = GetLayoutClass(*(void **)(obj + 8));
        if (lc != 0 && *(char **)(lc + 0x1A8) != 0 && **(char ***)(lc + 0x1A8) != 0) {
            cc = GetCharacterClass(*(void **)(obj + 8));
            if (cc != 0 && (s3 = *(int *)(cc + 0x750)) != 0 && (s2 = *(int *)(cc + 0x578)) != 0) {
                char *p = *(char **)(lc + 0x1A8);
                int n = dldCount((unsigned int *)(*(char **)p + 0x20));
                char *e = dldBase((unsigned int *)(*(char **)p + 0x20));
                float f = GetCharacterClassCurAnimationCurFrame(cc);
                int i;

                for (i = 0; i < n; i++, e += 0x18) {
                    char *a = dldResolve((unsigned int *)e);
                    char *b = dldResolve((unsigned int *)(e + 4));

                    if (a != 0 && a != (char *)s3)
                        continue;
                    if (b != 0 && b != (char *)s2)
                        continue;
                    if (!(*(float *)(e + 8) <= 0.0f || *(float *)(e + 8) <= f))
                        continue;
                    if (*(float *)(e + 0xC) <= 0.0f || f <= *(float *)(e + 0xC)) {
                        found = e;
                        break;
                    }
                }
            }
        }
    }
    return found != 0 ? *(int *)(found + 0x14) : 0;
}
#endif
