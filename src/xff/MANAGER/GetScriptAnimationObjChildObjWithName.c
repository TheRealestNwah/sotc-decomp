extern int strcmp(const char *, const char *);
typedef struct { int word0; char *name; int word8; } SubObjectName;
typedef struct { void *object; int value; } SubObject;
typedef struct { char pad[0x10]; SubObjectName *names; } NameResource;
typedef struct { char pad[0x328]; int *counts; int word32c; int word330; NameResource *names; SubObject *children; } ScriptAnimation;
static inline ScriptAnimation *getScriptAnimation(unsigned char *object)
{
    if (object[8] == 13)
        return (ScriptAnimation *)(object + 0x20);
    return 0;
}
void *GetScriptAnimationObjChildObjWithName(unsigned char *object, const char *name)
{
    ScriptAnimation *animation = getScriptAnimation(object);
    int *counts = animation->counts;
    int i = 0;
    if (*counts > 0) {
        int offset = 0;
        do {
            SubObjectName *entry = (SubObjectName *)(offset + (int)animation->names->names);
            if (strcmp(entry->name, name) == 0)
                return animation->children[i].object;
            offset += 12;
            ++i;
        } while (i < *counts);
    }
    return 0;
}
