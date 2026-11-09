typedef struct {
    int name;
    char *addr;
    int size;
    int align;
    unsigned int type;
    int flags;
    int pad18;
    int offset;
} XffSect;

typedef struct {
    char pad00[0x30];
    XffSect *sects;
    char pad34[0xC];
    int nsect;
    char pad44[0x8];
    int entry;
    char pad50[0xC];
    int shoff;
} XffHdr;

extern void iosJumpRecoverPoint(const char *, ...);
extern char RO_000428E0[];
extern char RO_00042940[];
extern char RO_000429A8[];

/* Matches only with -fno-strict-aliasing (config/ee_cflags.json). */
char *isysGetXffEntryPointPreRelocation(XffHdr *h)
{
    XffSect *s;
    int i;

    h->sects = (XffSect *)((char *)h + h->shoff);
    s = h->sects + 1;
    for (i = 1; i < h->nsect; i++, s++) {
        s->addr = (char *)h + s->offset;
        if (s->size == 0)
            continue;
        switch (s->type) {
        case 1:
        case 0x7FFFF420:
            if (s->flags != 0) {
                iosJumpRecoverPoint(RO_000428E0);
                break;
            }
            if ((int)s->addr & (s->align - 1)) {
                iosJumpRecoverPoint(RO_00042940, s->align);
                break;
            }
            return s->addr + h->entry;
        case 8:
            iosJumpRecoverPoint(RO_000429A8, s->align);
            break;
        }
    }
    return 0;
}
