extern char B_0015E350[];
extern void *memset(void *, int, unsigned int);

void init_camera_region_manager(void)
{
    memset(B_0015E350, 0, 0xC8);
}
