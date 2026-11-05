typedef struct {
    signed char type;
    char pad[3];
    short id;
    short pad2;
    int value[2];
} SheetEntry;

typedef struct {
    int pad;
    int count;
    SheetEntry *entries;
} Sheet;

extern int memcmp(const void *, const void *, unsigned int);
extern int sheetFsLanguageCode;

static int func_000E1030(Sheet *sheet, SheetEntry *key)
{
    SheetEntry *e = sheet->entries;
    int i;

    for (i = 0; i < sheet->count; i++, e++) {
        signed char t = e->type;

        if (key->type != t)
            continue;
        switch (key->type) {
        case 0:
        case 1:
            if (key->id == e->id)
                goto found;
            break;
        case 3:
        case 4:
            if (key->id == e->id)
                goto found_lang;
            break;
        case 2:
            key->id = 0;
            if (memcmp(key, e, 8) == 0)
                goto found;
            break;
        }
    }
    return -1;
found:
    return e->value[0];
found_lang:
    return e->value[sheetFsLanguageCode * 2];
}
