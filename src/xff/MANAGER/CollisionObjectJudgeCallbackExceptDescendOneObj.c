extern char *GetLayoutClass(void *);
extern void *GetLayoutParentObj(char *);

int CollisionObjectJudgeCallbackExceptDescendOneObj(void *obj, void *target)
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
