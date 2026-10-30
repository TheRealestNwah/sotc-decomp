extern char *GetLayoutClass(void *);
extern void UpdateLayoutClassPastGeometry(void *);

static void func_000347C8(char *obj)
{
    UpdateLayoutClassPastGeometry(GetLayoutClass(*(void **)(obj + 0x94)));
}
