typedef struct { char d[32]; } FontData;
extern FontData B_000C27B8[];

char *iosGetFontDataWithID(FontData *out, int idx, int id)
{
    FontData *f = &B_000C27B8[id];
    char *r = *(char **)(f->d + 8) + idx * (*(int *)(f->d + 0x10) * *(int *)(f->d + 0x14));
    if (out != 0)
        *out = *f;
    return r;
}
