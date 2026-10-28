typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
typedef struct {
    Vec4 pos;
    Vec4 dir;
    Vec4 target;
    int node;
    float time;
    float weight;
    int flag;
} PinAttackIK;
extern void *GetCharacterClass(void *);
extern int *DldSysUndefSymbol;
extern int CharIkTypeDef_PINATTACKIK[];

void SCRSetCharacterObjPinAttackIKTargetInfo(void *object, int index,
    const Vec4 *target, const unsigned int *targetObject, int flags)
{
    char *character = GetCharacterClass(object);
    PinAttackIK *ik = 0;
    if (DldSysUndefSymbol != CharIkTypeDef_PINATTACKIK &&
        *(int *)(character + 0x1100) == *CharIkTypeDef_PINATTACKIK) {
        ik = *(PinAttackIK **)(character + 0x1110) + (index & 0xFFFEFFFF);
    }
    if (ik != 0) {
        ik->node = targetObject ? ((*targetObject >> 18) & 0xFFF) : -1;
        ik->flag = flags;
        ik->target.q = target->q;
    }
}
