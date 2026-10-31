extern char *GetScriptCharacterClass(void *);

static void func_00048058(void *obj)
{
    char *c;
    void (*fn)(void *);

    c = GetScriptCharacterClass(obj);
    if (c != 0) {
        fn = *(void (**)(void *))(c + 0x11F8);
        if (fn != 0) {
            fn(obj);
        }
    }
}
