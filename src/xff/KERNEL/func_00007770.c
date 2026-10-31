typedef struct {
    unsigned char used;
    char pad1[0x3F];
} Entry;

typedef struct {
    int count;
    Entry *entries;
} Table;

static Entry *func_00007770(Table *table)
{
    Entry *entry = table->entries;
    int i;

    for (i = 0; i < table->count; i++, entry++) {
        if (entry->used == 0) {
            return entry;
        }
    }
    return 0;
}
