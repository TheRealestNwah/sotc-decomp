typedef struct AdpcmScriptWork {
    unsigned char unknown00[0x40];
    int field40;
    unsigned int flags;
} AdpcmScriptWork;
typedef struct AdpcmHandle { int handle; } AdpcmHandle;
typedef union AdpcmSlot AdpcmSlot;
union AdpcmSlot {
    struct {
        int state;
        unsigned char unknown04[0x14];
        AdpcmHandle *adpcm;
        AdpcmScriptWork *script;
        unsigned char unknown20[0x10];
        void (*callback)(AdpcmSlot *);
    } fields;
};
typedef struct AdpcmOrientEntry {
    unsigned char unknown00[0x40];
    AdpcmSlot *slot;
    unsigned char unknown44[0xC];
} AdpcmOrientEntry;
typedef struct AdpcmOrient {
    unsigned char unknown00[0xC];
    int count;
    AdpcmOrientEntry *entries;
} AdpcmOrient;
extern void adpcmDeleteAdpcmSeq(int);

static inline void clearScriptFlags(AdpcmScriptWork *script)
{
    script->flags &= ~2;
    script->flags &= ~1;
}

void deleteAdpcmOrient(AdpcmOrient *orient)
{
    int remaining;
    AdpcmOrientEntry *entry = orient->entries;
    if (orient->count > 0) {
        remaining = orient->count;
        do {
            if (entry->slot != 0) {
                AdpcmSlot *slot;
                adpcmDeleteAdpcmSeq(entry->slot->fields.adpcm->handle);
                slot = entry->slot;
                if (slot->fields.state != 5 && slot->fields.state != 6) {
                    clearScriptFlags(slot->fields.script);
                    slot->fields.state = 5;
                    slot->fields.script->field40 = 0;
                }
                if (slot->fields.callback != 0)
                    slot->fields.callback(slot);
            }
            entry++;
            remaining--;
        } while (remaining != 0);
    }
}
