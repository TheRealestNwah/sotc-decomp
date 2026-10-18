extern int strcmp(const char *, const char *);
extern char rootPtn[];
typedef struct { const char *name; int reserved; void *partition; } PartitionEntry;
typedef struct { char pad[12]; int count; PartitionEntry *entries; } PartitionConfig;
extern PartitionConfig *D_00130344;
void *getPartitionByName(const char *name)
{
    if (D_00130344) {
        int index = 1;
        PartitionEntry *entry = D_00130344->entries;
        entry++;
        for (; index < D_00130344->count; index++, entry++)
            if (strcmp(entry->name, name) == 0)
                return entry->partition;
    }
    return rootPtn;
}