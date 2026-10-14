extern void *GetSCRCharaAIWorkPtr(void *);
extern void *GetScriptCharacterClass(void *);

typedef int s128 __attribute__((mode(TI)));
#define NULL ((void *)0)
void getArrowPos(void *arg0, s128 *arg1) {
    if ((arg0 != NULL) && ((*(int *)((char *)(GetScriptCharacterClass(arg0)) + 0x1200)) != 0)) {
        (*(s128 *)((char *)(GetSCRCharaAIWorkPtr(arg0)) + 0x10)) = (s128) *arg1;
    }
}
