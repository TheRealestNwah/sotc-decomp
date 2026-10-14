extern void iosFree(void *);

void release_camera_context(void *p)
{
    if (p != 0) {
        iosFree(p);
    }
}
