typedef struct { const char *name; char unknown[8]; } SpecialFile;
typedef struct { int count; SpecialFile *entries; } SpecialFiles;
extern SpecialFiles B_00151800;
extern int strcmp(const char *, const char *);
SpecialFile *sheetFsSrhSpecialFs(const char *name)
{
    int i = 0;
    if (B_00151800.count > 0) {
        int offset = 0;
        do {
            SpecialFile *entry = (SpecialFile *)((char *)B_00151800.entries + offset);
            offset += sizeof(SpecialFile);
            if (strcmp(entry->name, name) == 0) return entry;
        } while (++i < B_00151800.count);
    }
    return 0;
}
