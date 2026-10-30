typedef struct {
    char pad0[0xC];
    unsigned short last;
    unsigned short first;
} GroupObj;

typedef struct {
    unsigned short first;
    unsigned short last;
} GroupHead;

typedef struct {
    GroupObj *obj;
    GroupHead *head;
    char pad8[4];
    unsigned char removed;
    char padD;
    unsigned short prev;
    unsigned short next;
    unsigned short objPrev;
    unsigned short objNext;
    char pad16[2];
} SysGroup;

extern SysGroup B_0006D640[];
extern SysGroup *B_000BF6C0;

static void func_00019AA8(SysGroup *node)
{
    GroupHead *head = node->head;
    GroupObj *obj = node->obj;

    if (node->prev)
        B_0006D640[node->prev].next = node->next;
    else if (head)
        head->last = node->next;
    if (node->next)
        B_0006D640[node->next].prev = node->prev;
    else if (head)
        head->first = node->prev;
    if (node->objPrev)
        B_0006D640[node->objPrev].objNext = node->objNext;
    else
        obj->first = node->objNext;
    if (node->objNext)
        B_0006D640[node->objNext].objPrev = node->objPrev;
    else
        obj->last = node->objPrev;
    node->obj = 0;
    node->removed = 0;
    node->prev = B_000BF6C0 ? B_000BF6C0 - B_0006D640 : 0;
    B_000BF6C0 = node;
}
