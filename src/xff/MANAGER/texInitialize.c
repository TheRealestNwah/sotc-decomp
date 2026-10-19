typedef struct Node { int used; int a; struct Node *prev; struct Node *next; } Node;
extern Node *D_00136274;
extern unsigned char B_00148A00[];
extern void *func_0002DBA8(void *);
extern int isysAddGroupWithLinkParam(void *, void *, int, int);

void texInitialize(char *object, char *request)
{
    char *texture;
    char *work;
    Node *node;
    Node *next;
    func_0002DBA8(object);
    texture = *(char **)(object + 0x20);
    work = *(char **)(texture + 0xC);
    *(char **)(work + 0x34) = work;
    node = (Node *)(work + 0x30);
    next = D_00136274;
    node->used = 1;
    node->prev = 0;
    node->next = next;
    if (next)
        next->prev = node;
    D_00136274 = node;
    isysAddGroupWithLinkParam(object, B_00148A00, 0, 0);
    if (request) {
        *(char **)(request + 0xC) = object;
        ++*(int *)(request + 0x10);
    }
}
