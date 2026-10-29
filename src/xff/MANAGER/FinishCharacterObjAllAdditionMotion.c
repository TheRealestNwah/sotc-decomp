typedef struct { char pad0[0xA8]; void (*leave[2])(void *); } AdditionMotion;
typedef struct {
    int unknown0; AdditionMotion *motion;
    char pad8[0x3C]; int state;
    char pad48[0x38];
} AdditionSlot;
typedef struct {
    char pad0[0x2C8]; char callbacks[0x44];
    AdditionSlot *additions; char pad310[0xEC]; int count;
} CharacterClass;
extern CharacterClass *GetCharacterClass(void *);
extern int CallMotShiftCallBackElemLeaveFunc(void *, int, void *);
extern void ReleaseCharacterClassAddMotSyncAnim(void *);
static inline void finishAddition(void *actor, AdditionSlot *slot)
{
    CharacterClass *character = GetCharacterClass(actor);
    AdditionMotion *motion = slot->motion;
    int i;
    slot->state = -2;
    for (i = 0; i < 2; i++) {
        if (motion->leave[i] != 0)
            motion->leave[i](actor);
    }
    CallMotShiftCallBackElemLeaveFunc(character->callbacks, (int)motion, actor);
    CallMotShiftCallBackElemLeaveFunc(character->callbacks, (int)motion, actor);
    ReleaseCharacterClassAddMotSyncAnim(slot);
}
void FinishCharacterObjAllAdditionMotion(void *actor)
{
    CharacterClass *character = GetCharacterClass(actor);
    int i;
    for (i = 0; i < character->count; i++) {
        AdditionSlot *slot = &character->additions[i];
        if (slot->state == 0)
            finishAddition(actor, slot);
    }
}
