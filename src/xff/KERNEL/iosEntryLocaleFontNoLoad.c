typedef struct { char d[32]; } Font;
extern Font B_000C27B8;

int iosEntryLocaleFontNoLoad(int id, Font *f)
{
    B_000C27B8 = *f;
    *(int *)((char *)&B_000C27B8 + 8) = id;
    return id;
}
