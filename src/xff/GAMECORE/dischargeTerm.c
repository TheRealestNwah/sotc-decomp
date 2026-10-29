typedef struct Object Object;
extern int getSpecialEffectObjWork(void *);
extern void isysRequestDeleteObj(Object *);

void dischargeTerm(void *actor)
{
    char *work = (char *)getSpecialEffectObjWork(actor);
    isysRequestDeleteObj(*(Object **)(work + 0x10));
}
