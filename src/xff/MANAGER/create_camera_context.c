extern char rootPtn[];
extern void *iosMallocAlign(void *, int, int);
extern void constructor_camera_context(void *);

void *create_camera_context(void)
{
    void *c = iosMallocAlign(rootPtn, 0x6A0, 0x10);
    constructor_camera_context(c);
    return c;
}
