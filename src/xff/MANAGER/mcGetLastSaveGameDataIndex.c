typedef struct {
    char pad0[0xC];
    int active;
    char pad10[0x30];
    unsigned long timestamp;
    char pad48[0x50];
} SaveRecord;
typedef struct {
    char pad0[0x4C];
    int has_last;
    int last_index;
    char pad54[0x84];
    SaveRecord records[10];
} SaveWork;
extern unsigned long *D_0013770C;

int mcGetLastSaveGameDataIndex(SaveWork *work)
{
    int i;
    int result;
    if (D_0013770C != 0) {
        for (i = 0; i < 10; i++) {
            SaveRecord *record = &work->records[i];
            if (record->active == 1 && *D_0013770C == record->timestamp)
                goto found;
        }
    }
    result = work->has_last != 0 ? work->last_index : -1;
    goto done;
found:
    return i;
done:
    return result;
}
