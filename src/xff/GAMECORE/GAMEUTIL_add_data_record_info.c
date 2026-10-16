typedef struct {
    int size;
    int max;
    char *buf;
    int n;
} DataRecord;

extern void *memcpy(void *, const void *, unsigned int);

void GAMEUTIL_add_data_record_info(DataRecord *r, void *data)
{
    int size = r->size;
    char *buf = r->buf;
    int i;

    if (r->n < r->max)
        r->n++;
    else
        r->n = r->max;
    for (i = r->n - 1; i > 0; i--)
        memcpy(buf + i * size, buf + (i - 1) * size, size);
    memcpy(buf, data, size);
}
