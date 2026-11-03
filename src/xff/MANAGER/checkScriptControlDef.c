typedef struct {
    int pad;
    int bit;
    int mode;
} ScriptControlDef;

int checkScriptControlDef(long flags, ScriptControlDef *def, int val)
{
    long hit;

    if (def == 0) {
        return val;
    }
    hit = flags & (1L << def->bit);
    switch (def->mode) {
    case 1:
    default:
        return hit ? 1 : val;
    case 2:
        return hit ? 0 : val;
    }
}
