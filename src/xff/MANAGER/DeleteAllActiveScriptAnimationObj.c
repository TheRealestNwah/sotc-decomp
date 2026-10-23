typedef struct {
    unsigned char pad[0x16];
    short flags;
} AnimationResource;
typedef struct {
    unsigned char pad[0x32C];
    AnimationResource *resource;
    unsigned char pad330[0x18];
    int *completed;
    unsigned char pad34C[0x18];
    signed char state;
} ScriptAnimation;
extern struct {
    unsigned char pad[12];
    void *animationGroup;
} info;
extern void **isysGroupForFirst(void *, int);
extern void **isysGroupForNext(void **, int);
extern void isysGroupForExit(void *, int);
extern void isysRequestDeleteObj(void *);

static inline ScriptAnimation *animationClass(unsigned char *object)
{
    if (object[8] != 13)
        return 0;
    return (ScriptAnimation *)(object + 0x20);
}

void DeleteAllActiveScriptAnimationObj(void)
{
    void **iterator;
    unsigned char *object = 0;
    for (iterator = isysGroupForFirst(info.animationGroup, 0);
         iterator != 0; iterator = isysGroupForNext(iterator, 0)) {
        ScriptAnimation *animation;
        int state;
        object = *iterator;
        animation = animationClass(object);
        state = animation->state;
        if (state >= 3) {
            if ((state < 5 || state == 6) && (animation->resource->flags & 1)) {
                if (animation->completed)
                    *animation->completed = 1;
                isysRequestDeleteObj(object);
            }
        }
    }
    if (object)
        isysGroupForExit(object, 0);
}
