/* Parked at 9 diffs: the Original loads anim->frame before anim->motion and swaps v0/v1 for motion and its flags. */
#ifdef NONMATCHING
typedef struct {
    char pad0[0x18];
    unsigned int flags;
    char pad1C[0x34];
    char res[0xC];
    int frames;
    char pad60[0x48];
    void (*leave[2])(void *);
} AdditionMotion;
typedef struct {
    AdditionMotion *motion;
    int pad4;
    float frame;
    float prev;
} AdditionAnim;
typedef struct {
    int unknown0;
    AdditionAnim anim;
    char pad14[0x30];
    int state;
    char pad48[8];
    float length;
    float rate;
    char pad58[0x28];
} AdditionSlot;
typedef struct {
    char pad0[0x2C8];
    char callbacks[0x44];
    AdditionSlot *additions;
    char pad310[0x64];
    float speed;
    char pad378[0x84];
    int count;
    char pad400[0x124];
    float speedScale;
} CharacterClass;
extern CharacterClass *GetCharacterClass(void *);
extern int CallMotShiftCallBackElemLeaveFunc(void *, int, void *);
extern void ReleaseCharacterClassAddMotSyncAnim(void *);
extern int GetAnimationClassCurrentInfo(AdditionAnim *, void *, float, float);
extern int GetMotionResourceFrames(void *);
static inline void finishAddition(void *actor, AdditionSlot *slot)
{
    CharacterClass *character = GetCharacterClass(actor);
    AdditionMotion *motion = slot->anim.motion;
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
static void func_00051CA0(void *actor, float t)
{
    CharacterClass *character = GetCharacterClass(actor);
    int i;
    for (i = 0; i < character->count; i++) {
        AdditionSlot *slot = &character->additions[i];
        if (slot->state == -1)
            finishAddition(actor, slot);
        if (slot->state >= 0) {
            AdditionAnim *anim = &slot->anim;
            AdditionMotion *motion;
            void *res;
            float frames;
            anim->prev = anim->frame;
            motion = anim->motion;
            res = motion->res;
            frames = motion->frames;
            if ((motion->flags >> 1) & 1)
                frames *= character->speed * character->speedScale;
            if (GetAnimationClassCurrentInfo(anim, res, frames, t)) {
                slot->state = -1;
                anim->frame = GetMotionResourceFrames(res);
            }
            if (slot->length != 0.0f) {
                float r = 1.0f;
                if (!(slot->length < anim->frame))
                    r = anim->frame / slot->length;
                slot->rate = r;
            } else
                slot->rate = 1.0f;
        }
    }
}
#endif
