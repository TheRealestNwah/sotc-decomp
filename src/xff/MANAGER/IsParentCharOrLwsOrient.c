typedef struct {
    char pad[0x20];
    char body[0x124];
    int parent;
} CharObj;

typedef struct {
    CharObj *chr;
    char pad[0x4C];
} LwsOriEntry;

typedef struct {
    char pad[0x30];
    int num;
} LwsOriInfo;

typedef struct {
    char pad[0x11F8];
    LwsOriInfo *info;
    int pad11FC;
    LwsOriEntry *entries;
} LwsOriClass;

typedef struct {
    char pad[0x124];
    int parent;
} LayoutClass;

extern LwsOriClass *GetScrLwsOriClass(void *);
extern LayoutClass *GetLayoutClass(void *);

void *IsParentCharOrLwsOrient(void *obj)
{
    LwsOriClass *lws = GetScrLwsOriClass(obj);
    void *result = 0;
    LayoutClass *layout;
    LwsOriEntry *e;
    int i;

    if (lws != 0) {
        e = lws->entries;
        for (i = 0; i < lws->info->num; i++, e++) {
            if (e->chr != 0 && e->chr->parent != 0) {
                result = e->chr->body;
                break;
            }
        }
    } else {
        layout = GetLayoutClass(obj);
        result = layout;
        if (layout->parent == 0) {
            result = 0;
        }
    }
    return result;
}
