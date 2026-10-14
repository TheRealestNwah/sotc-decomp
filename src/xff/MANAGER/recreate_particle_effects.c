extern void iosFree(int);

extern int malloc_from_root_partition(int, void *);
extern unsigned char RO_00140B70[];

int recreate_particle_effects(void *arg0, int arg1) {
    int temp_v0;
    int temp_v0_2;

    temp_v0_2 = (*(int *)((char *)(arg0) + 0xD4));
    if (temp_v0_2 != 0) {
        iosFree(temp_v0_2);
    }
    (*(int *)((char *)(arg0) + 0xD0)) = arg1;
    temp_v0 = malloc_from_root_partition(arg1 * 0x1BC, RO_00140B70);
    (*(int *)((char *)(arg0) + 0xD4)) = temp_v0;
    return temp_v0 != 0;
}
