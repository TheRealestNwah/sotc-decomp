typedef struct { int name; int value; int size; unsigned char info; unsigned char other; unsigned short shndx; } Sym;
typedef struct { unsigned int offset; unsigned int info; } Rel;
typedef struct { int type; unsigned int count; int shdr; Rel *rels; char pad10[0xC]; } RelSect;
typedef struct { int addr; char pad4[0x1C]; } Shdr;
typedef struct {
    char pad0[0x28];
    Sym *syms;
    char *strtab;
    Shdr *shdrs;
    char pad34[4];
    int nsects;
    RelSect *sects;
} ModInfo;
typedef struct { char pad0[0x1C]; ModInfo *info; } Module;

extern char symbolDefModuleGroup[];
extern void **isysGroupForFirst(void *, int);
extern void **isysGroupForNext(void **, int);
extern void isysGroupForExit(void *, int);

#ifdef NONMATCHING
/* Parked: 62 words differ. Control flow and frame match except register
 * pressure: the original keeps the type constants 4 and 9 in s3/s2 and the
 * module pointer in s4 with a 0x30 frame. Permuter stalled around 1500. */
static int func_0000AF78(int addr)
{
    Module *mod = 0;
    int r = 0;
    void **link;

    for (link = isysGroupForFirst(symbolDefModuleGroup, 0); link != 0; link = isysGroupForNext(link, 0)) {
        ModInfo *info;
        mod = *link;
        info = mod->info;
        for (r = 0; r < info->nsects; r++) {
            if (info->sects[r].type == 4 || info->sects[r].type == 9) {
                RelSect *s = &info->sects[r];
                unsigned int j;
                Rel *rl = s->rels;
                for (j = 0; j < s->count; j++, rl++) {
                    Sym *sym = &info->syms[rl->info >> 8];
                    if (sym->shndx == 0 && info->shdrs[s->shdr].addr + rl->offset == addr) {
                        r = (int)(info->strtab + sym->name);
                        goto done;
                    }
                }
            }
        }
        r = 0;
    done:
        if (r != 0)
            break;
    }
    if (mod != 0)
        isysGroupForExit(mod, 0);
    return r;
}
#endif
