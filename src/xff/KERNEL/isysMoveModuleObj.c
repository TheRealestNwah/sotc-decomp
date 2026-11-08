typedef struct {
    char pad0[4];
    int value;
    char pad8[5];
    unsigned char undef;
    unsigned short shndx;
} Sym;

typedef struct {
    int heap;
    char pad4[8];
    unsigned char first;
    char padD[3];
    int unk10;
    char pad14[8];
    int nidx;
    int *idx;
    int nsym;
    Sym *syms;
} ModInfo;

typedef struct Ref {
    char pad0[4];
    Sym *sym;
    int unk8;
    struct Ref *next;
} Ref;

typedef struct {
    char pad0[4];
    Ref *refs;
    Sym *sym;
    char padC[4];
} Import;

typedef struct {
    char pad0[4];
    Sym *sym;
    char pad8[8];
} Export;

typedef struct {
    unsigned int rest : 29;
    unsigned int c : 1;
    unsigned int b : 1;
    int a : 1;
} ModFlags;

typedef struct {
    int heap;
    char pad4[0x18];
    ModInfo *info;
    int unk20;
    Import *imports;
    Export *exports;
    ModFlags flags;
} ModObj;

extern char D_0000A208[];
extern int func_0000A298();
extern int func_000077C0();
extern int DldSysUndefSymbol;
extern ModInfo *func_00007B78(ModInfo *, ModObj *, int, void *, void *, int, void *, int);

/* Parked: Parked: 61 words differ (DldSysUndefSymbol address kept across the call, start index if-converted to movz) */
#ifdef NONMATCHING
void isysMoveModuleObj(ModObj *obj, ModInfo *info)
{
    Sym *syms;

    func_00007B78(info, obj, obj->heap, D_0000A208, func_0000A298, DldSysUndefSymbol, func_000077C0, 0);
    obj->unk20 = info->unk10;
    obj->info = info;
    obj->flags.c = 0;
    if (obj->flags.a) {
        Import *imp = obj->imports;
        if (imp != 0) {
            int start = info->first + 1;
            int n;
            Sym *s;
            if (info->first == 0) {
                start = 2;
            }
            n = info->nsym - start;
            syms = info->syms;
            s = &syms[start];
            while (n-- != 0) {
                if (s->shndx != 0) {
                    if (imp->sym != 0) {
                        Ref *r = imp->refs;
                        imp->sym = s;
                        imp->refs = 0;
                        while (r != 0) {
                            Sym *rs = r->sym;
                            Ref *next = r->next;
                            rs->undef = 1;
                            rs->value = DldSysUndefSymbol;
                            r->unk8 = 0;
                            r->next = 0;
                            r = next;
                        }
                    }
                    imp++;
                }
                s++;
            }
        }
        syms = info->syms;
        {
            Export *e = obj->exports;
            int *idx = info->idx;
            int n = info->nidx;
            while (n-- != 0) {
                e->sym = &syms[*idx++];
                e++;
            }
        }
    }
}
#else
extern void isysMoveModuleObj(ModObj *obj, ModInfo *info);
#endif
