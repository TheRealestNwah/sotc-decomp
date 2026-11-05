typedef struct {
    char pad0[0x20];
    int unk20;
    char pad24[0x14];
    int *unk38;
    int *unk3C;
} ScriptClass;

typedef struct {
    int unk0;
    int unk4;
    int unk8;
    int unkC;
    void *unk10;
} IntrDef;

typedef struct {
    void *unk0;
    int unk4;
    int *unk8;
} IntrNode;

extern char rootPtn[];
extern IntrNode *isysGroupForFirst(void *, int);
extern IntrNode *isysGroupForNext(IntrNode *, int);
extern void isysGroupForExit(void *, int);
extern ScriptClass *GetScriptClass(void *);
extern void *createScriptObj(int, int, void *, int, int, int, void *, int);

void scriptIntrSignal(long *sig)
{
    IntrNode *node;
    IntrNode *n2;
    void *last;
    ScriptClass *cls;
    IntrDef *d;

    if ((int)(*sig >> 32) & 1) {
        last = 0;
        for (node = isysGroupForFirst((char *)sig + 8, 0); node != 0; node = isysGroupForNext(node, 0)) {
            last = node->unk0;
            cls = GetScriptClass(node->unk0);
            if (cls->unk38 == 0 || *cls->unk38 < *(int *)sig) {
                cls->unk38 = (int *)sig;
                cls->unk3C = node->unk8;
            }
        }
        if (last != 0) {
            isysGroupForExit(last, 0);
        }
    }
    if ((int)((unsigned long)*sig >> 33) & 1) {
        last = 0;
        for (n2 = isysGroupForFirst((char *)sig + 0x10, 0); n2 != 0; n2 = isysGroupForNext(n2, 0)) {
            last = n2->unk0;
            d = (IntrDef *)n2->unk8;
            cls = GetScriptClass(d->unk10);
            createScriptObj(d->unk4, d->unk8, rootPtn, 0x1000, 0, cls->unk20, d->unk10, 0);
        }
        if (last != 0) {
            isysGroupForExit(last, 0);
        }
    }
}
