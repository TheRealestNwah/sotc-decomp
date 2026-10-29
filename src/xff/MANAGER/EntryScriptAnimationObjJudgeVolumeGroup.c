typedef struct { int type, group, unknown; } ScriptGroupEntry;
typedef struct {
    int count;
    char pad4[0x14];
    ScriptGroupEntry *entries;
} ScriptGroupResource;
typedef struct { void *object; int unknown; } ScriptChild;
typedef struct {
    char pad0[0x328];
    ScriptGroupResource *resource;
    char pad32C[0xC];
    ScriptChild *children;
} ScriptAnimationClass;
extern int EntryJudgeVolumeClassObjectGroup(char *, int, void *);
static inline ScriptAnimationClass *get_script_class(unsigned char *object)
{
    if (object[8] != 0xD)
        return 0;
    return (ScriptAnimationClass *)(object + 0x20);
}

static void EntryScriptAnimationObjJudgeVolumeGroup(unsigned char *object, char *volume)
{
    ScriptAnimationClass *script = get_script_class(object);
    ScriptGroupResource *resource = script->resource;
    int count = resource->count;
    ScriptGroupEntry *entry = resource->entries;
    int index;
    for (index = 0; index < count; index++) {
        void *child = script->children[index].object;
        if (child != 0 && (entry->type == 0x2C || entry->type == 0x2E))
            EntryJudgeVolumeClassObjectGroup(volume, entry->group - 1, child);
        entry++;
    }
}
