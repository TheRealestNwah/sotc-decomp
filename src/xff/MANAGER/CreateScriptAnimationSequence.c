typedef struct {
    int words[11];
} ScriptAnimationGlobalBaseInfo;

typedef struct {
    int *res;
    int parent;
    int a8;
    int aC;
    int a10;
    int a14;
    int a18;
    int a1C;
    int a20;
    int a24;
    int a28;
} SeqParam;

typedef struct {
    int w0;
    int w4;
    int pad8[7];
    int w24;
    int pad28;
    int w2C;
    int w30;
    int w34;
    int pad38;
    int w3C;
    int pad40[15];
} SeqHead;

typedef struct {
    SeqHead head;
    int w7C;
    int w80;
    int w84;
    int w88;
    int w8C;
    int w90;
    int w94;
    int w98;
    int w9C;
    int wA0;
    int wA4;
    int wA8;
    int *wAC;
    int wB0;
    int wB4;
    int wB8;
    int wBC;
} __attribute__((aligned(16))) SeqCreate;

extern ScriptAnimationGlobalBaseInfo info;
extern void *memset(void *, int, unsigned int);
extern void *CreateScriptAnimationObj(int, int, SeqCreate);
extern void isysAddGroupWithLinkParam(void *, int, int, int);

#ifdef NONMATCHING
/* 17 diffs: store order of the SeqCreate fields and copy-loop registers */
void *CreateScriptAnimationSequence(SeqParam *p)
{
    SeqCreate arg;
    SeqCreate c;
    void *obj;
    int *res;
    int t;

    memset(&c.head, 0, sizeof(c.head));
    res = p->res;
    t = p->a1C;
    c.head.w0 = *res;
    c.head.w4 = 1;
    c.head.w24 = p->a8;
    c.head.w2C = p->aC;
    c.head.w30 = p->a10;
    c.head.w34 = p->a14;
    c.head.w3C = 7;
    if (t == 0)
        t = info.words[6];
    c.w84 = p->a28 < 0 ? 0x800 : p->a28;
    c.w88 = info.words[7];
    c.w8C = p->a18;
    c.wA4 = info.words[1];
    c.wA8 = info.words[2];
    c.wAC = res;
    c.wBC = p->a24;
    c.w80 = 0;
    c.w90 = 0;
    c.w94 = 0;
    c.w98 = 0;
    c.w9C = 0;
    c.wA0 = 0;
    c.wB0 = 0;
    c.wB4 = 0;
    c.wB8 = 0;
    c.w7C = t;
    arg = c;
    obj = CreateScriptAnimationObj(p->parent, 0, arg);
    if (obj != 0) {
        isysAddGroupWithLinkParam(obj, info.words[1], 0, 0);
        isysAddGroupWithLinkParam(obj, info.words[3], 0, 0);
    }
    return obj;
}
#endif
