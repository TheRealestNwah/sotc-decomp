/* Two DMA tag quadwords, written through a union (alias set 0). */
typedef union TexTransDma {
    long dword[4];
    int word[8];
} TexTransDma;

/* Counter updates go through a union, so they complete before the next object's loads. */
typedef union TexTransCount {
    struct {
        char pad0[0x24];
        int count;
    } s;
} TexTransCount;

typedef struct TexTransGroup {
    char pad0[0xC];
    TexTransCount *counter;
} TexTransGroup;

typedef struct TexTransObj {
    char pad0[0x20];
    TexTransGroup *group;
} TexTransObj;

typedef struct TexTransReq TexTransReq;

/* List links are stored through a union, so each store reloads the list pointers. */
typedef union TexTransLink {
    TexTransReq *req;
} TexTransLink;

struct TexTransReq {
    union {
        int word[2];
    } head;
    int param;
    int padC;
    TexTransObj *obj[2];
    TexTransDma *dma;
    TexTransLink next;
};

extern void iosDlLockObj(TexTransObj *);
extern void *iosAllocPacketPtrPath1(int);
extern void iosDlChainTailCurrent(void *);
extern int iosDlGetLayer(void);

/* Per-layer request list heads and tails. As aggregates, their loads are not
   assumed independent of the request stores, so each store reloads them. */
typedef struct TexTransQueue {
    TexTransReq **list;
} TexTransQueue;

extern TexTransQueue B_00148A04;
extern TexTransQueue B_00148A08;

static inline void texTransSetTags(TexTransDma *dma)
{
    dma->dword[2] = 0x60000000;
    dma->dword[0] = 0x60000000;
}

static inline void texTransClearHigh(TexTransDma *dma, int i)
{
    dma->word[i + 1] = 0;
    dma->word[i] = 0;
}

static inline void texTransSetDma(TexTransReq *req, int param)
{
    req->dma = iosAllocPacketPtrPath1(0x20);
    __asm__ __volatile__("pref 0, 0x40(%0)" : : "r"(req->dma));
    texTransSetTags(req->dma);
    texTransClearHigh(req->dma, 2);
    texTransClearHigh(req->dma, 6);
    req->param = param;
    iosDlChainTailCurrent(req->dma);
}

static inline void texTransAppend(TexTransReq *req)
{
    int layer = iosDlGetLayer();

    req->next.req = 0;
    if (B_00148A04.list[layer] == 0) {
        B_00148A04.list[layer] = req;
    }
    if (B_00148A08.list[layer] != 0) {
        B_00148A08.list[layer]->next.req = req;
    }
    B_00148A08.list[layer] = req;
}

void texTransRequest(TexTransObj *obj, int param, int slot)
{
    TexTransReq *req;

    iosDlLockObj(obj);
    req = iosAllocPacketPtrPath1(0x20);
    __asm__ __volatile__("pref 0, 0x40(%0)" : : "r"(req));
    req->head.word[0] = 0;
    req->head.word[1] = 0;
    req->obj[slot] = obj;
    req->obj[slot ? 0 : 1] = 0;
    texTransSetDma(req, param);
    obj->group->counter->s.count++;
    texTransAppend(req);
}

void texTransRequestMulti(TexTransObj *obj0, TexTransObj *obj1, int param)
{
    TexTransReq *req;

    if (obj0 == 0 || obj1 == 0) {
        return;
    }
    iosDlLockObj(obj0);
    iosDlLockObj(obj1);
    req = iosAllocPacketPtrPath1(0x20);
    __asm__ __volatile__("pref 0, 0x40(%0)" : : "r"(req));
    req->head.word[0] = 0;
    req->head.word[1] = 0;
    req->obj[0] = obj0;
    req->obj[1] = obj1;
    texTransSetDma(req, param);
    obj0->group->counter->s.count++;
    obj1->group->counter->s.count++;
    texTransAppend(req);
}
