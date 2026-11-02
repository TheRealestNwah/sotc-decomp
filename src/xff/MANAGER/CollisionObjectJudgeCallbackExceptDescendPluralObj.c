extern char *GetLayoutClass(void *);
extern void *GetLayoutParentObj(char *);

static inline int exceptDescendOneObj(void *obj, void *target)
{
    char *layout;

    if (target != 0) {
        for (; obj != 0; obj = layout ? (*(void **)(layout + 0x194) ? *(void **)(layout + 0x194) : GetLayoutParentObj(layout)) : 0) {
            if (obj == target)
                return 0;
            layout = GetLayoutClass(obj);
        }
    }
    return 1;
}

int CollisionObjectJudgeCallbackExceptDescendPluralObj(void *obj, int *list)
{
    int i;

    for (i = 0; i < list[0]; i++) {
        if (!exceptDescendOneObj(obj, (void *)list[i + 1]))
            return 0;
    }
    return 1;
}
