typedef struct { int type; int words[2]; } SubObjectType;
typedef struct { void *object; int value; } SubObject;
typedef struct { int count; char pad[0x14]; SubObjectType *types; } AnimationResource;
typedef struct { char pad[0x328]; AnimationResource *resource; char pad32c[0xc]; SubObject *children; } ScriptAnimation;
void GetScriptAnimationSubObjectWithTypeFiltering(unsigned char *object, int type, void (*callback)(void *, void *), void *context)
{
    ScriptAnimation *animation = object[8] == 13 ? (ScriptAnimation *)(object + 0x20) : 0;
    AnimationResource *resource = animation->resource;
    SubObject *child = animation->children;
    SubObjectType *entry = resource->types;
    int remaining;
    for (remaining = resource->count; --remaining != -1; ++entry, ++child) {
        if ((type < 0 || entry->type == type) && child->object != 0)
            callback(child->object, context);
    }
}

