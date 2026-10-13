extern int GetGeoDispClass(int);
extern void func_000BF528(int);
extern void isysRequestDeleteObj(int);

void check_free_particle_geodisp(int *arg0)
{
    int temp_v0;

    temp_v0 = *arg0;
    if (temp_v0 != 0) {
        func_000BF528(GetGeoDispClass(temp_v0) + 0xE8);
        isysRequestDeleteObj(*arg0);
        *arg0 = 0;
    }
}
