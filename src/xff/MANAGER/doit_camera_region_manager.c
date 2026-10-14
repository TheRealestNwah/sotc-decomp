extern void doit_camera_region(void *, void *, float);
extern void *B_0015E350[];

void doit_camera_region_manager(void *actor, float interval)
{
    void **entry;
    void *region;
    int remaining;

    remaining = 0x31;
    entry = B_0015E350;
    do {
        region = *entry;
        entry++;
        if (region != 0) {
            doit_camera_region(region, actor, interval);
        }
        remaining--;
    } while (remaining >= 0);
}
