extern void *GetGeoDispClass(int);
extern void isysRequestDeleteObj(int);

int auto_end_check_and_check_free_particle_geodisp(int *arg0)
{
    int temp_v0;

    temp_v0 = *arg0;
    if ((temp_v0 != 0) && ((*(int *)((char *)(GetGeoDispClass(temp_v0)) + 0xE8)) == 0)) {
        isysRequestDeleteObj(*arg0);
        *arg0 = 0;
        return 1;
    }
    return 0;
}
