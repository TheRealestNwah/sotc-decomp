#define NULL ((void *)0)
extern void *GetScriptCharacterClass(void *);

void GexCutTail(void *actor) {
    int *temp_v1;
    void *temp_v0;

    temp_v0 = (*(void **)((char *)(GetScriptCharacterClass(actor)) + 0x1200));
    if (temp_v0 != NULL) {
        temp_v1 = (*(int **)((char *)(temp_v0) + 0x10));
        if (temp_v1 != NULL) {
            *temp_v1 = 1;
        }
    }
}
