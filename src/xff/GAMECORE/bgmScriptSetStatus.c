typedef struct BgmScriptWork {
    char pad0[0x34];
    int endType;
    float endFade;
    char pad3C[4];
    int field40;
    unsigned int flags;
} BgmScriptWork;

typedef union BgmScriptSlot BgmScriptSlot;
/* Slot control stores may alias the script pointer in the shared work table. */
union BgmScriptSlot {
    struct {
        int state;
        char pad4[0x18];
        BgmScriptWork *script;
        char pad20[4];
        float fade;
        char pad28[8];
        void (*callback)(BgmScriptSlot *);
        char pad34[0xC];
    } fields;
};

extern int D_0017A930;
extern BgmScriptSlot B_001887D0[3];

static inline void clearScriptFlags(BgmScriptWork *script)
{
    script->flags &= ~2;
    script->flags &= ~1;
}

void bgmScriptSetStatus(int status)
{
    int i;

    D_0017A930 = status;
    if (status == 1) {
        for (i = 0; i < 3; i++) {
            BgmScriptSlot *slot = &B_001887D0[i];

            if (slot->fields.state != 0) {
                if (slot->fields.state != 5 && slot->fields.state != 6) {
                    clearScriptFlags(slot->fields.script);
                    slot->fields.state = 5;
                    slot->fields.script->field40 = 0;
                }
                if (slot->fields.callback != 0) {
                    slot->fields.callback(slot);
                }
            }
        }
    }
}

void bgmPlayerDemoEndTypeAllClose(void)
{
    int i;

    for (i = 0; i < 3; i++) {
        BgmScriptSlot *slot = &B_001887D0[i];
        int state = slot->fields.state;

        if (state != 0) {
            BgmScriptWork *script = slot->fields.script;

            if (script->endType == 4) {
                slot->fields.fade = script->endFade;
                if (state != 5 && state != 6) {
                    clearScriptFlags(script);
                    slot->fields.state = 5;
                    slot->fields.script->field40 = 0;
                }
                if (slot->fields.callback != 0) {
                    slot->fields.callback(slot);
                }
            }
        }
    }
}
