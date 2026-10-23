extern void *GetGeoDispClass(void *obj);
extern void func_000BF850(void *disp);

void doit_particle_geodisp(void *obj)
{
    func_000BF850(obj ? (char *)GetGeoDispClass(obj) + 0xE8 : 0);
}
