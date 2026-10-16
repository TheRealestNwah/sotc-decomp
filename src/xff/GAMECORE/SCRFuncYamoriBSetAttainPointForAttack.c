typedef int s128 __attribute__((mode(TI)));

extern char *GetSCRCharaAIWorkPtr(void *);
extern char *getSCRDataCtrlWork(void *);
extern void func_000D1A80(void *, void *, int, int);
extern void setAttainmentPos(void *, void *);

void SCRFuncYamoriBSetAttainPointForAttack(void *actor, int a1, int point)
{
    s128 pos;
    char *ai;
    char *work;

    ai = GetSCRCharaAIWorkPtr(actor);
    work = getSCRDataCtrlWork(actor);
    func_000D1A80(actor, &pos, 1, point);
    setAttainmentPos(work, &pos);
    *(s128 *)(ai + 0x41F0) = pos;
    *(int *)(ai + 0x41C8) = 0;
}
