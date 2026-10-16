extern void iosFree(void *p);

void unloadCdNfbFile(void *a, void *b, void *buf)
{
    if (buf) {
        iosFree(buf);
    }
}
