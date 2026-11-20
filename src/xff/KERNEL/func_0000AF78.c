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
/* Parked: 43 words differ. Control flow and frame match. A separate return
 * variable keeps the section counter a biv, and the type checks go through a
 * stepping pointer. The original reduces &info->sects[r] to a byte-offset giv
 * plus a base copy (all ten t-regs busy, constants 4/9 in s3/s2, the module
 * pointer in s4); this draft makes a second pointer biv instead. Permuter
 * stalled. */
static int func_0000AF78(int addr)
{
    Module *mod = 0;
    int ret = 0;
    void **link;

    for (link = isysGroupForFirst(symbolDefModuleGroup, 0); link != 0; link = isysGroupForNext(link, 0)) {
        ModInfo *info;
        int r;
        RelSect *p;
        mod = *link;
        info = mod->info;
        p = info->sects;
        for (r = 0; r < info->nsects; r++, p++) {
            if (p->type == 4 || p->type == 9) {
                RelSect *s = &info->sects[r];
                unsigned int j;
                Rel *rl = s->rels;
                for (j = 0; j < p->count; j++, rl++) {
                    Sym *sym = &info->syms[rl->info >> 8];
                    if (sym->shndx == 0 && info->shdrs[s->shdr].addr + rl->offset == addr) {
                        ret = (int)(info->strtab + sym->name);
                        goto done;
                    }
                }
            }
        }
        ret = 0;
    done:
        if (ret != 0)
            break;
    }
    if (mod != 0)
        isysGroupForExit(mod, 0);
    return ret;
}
#endif
