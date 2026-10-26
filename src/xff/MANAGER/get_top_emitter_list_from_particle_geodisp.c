extern char *GetGeoDispClass(unsigned char *obj);

void **get_top_emitter_list_from_particle_geodisp(unsigned char *obj)
{
    if (obj != 0) {
        return (void **)(GetGeoDispClass(obj) + 0xE8);
    }
    return 0;
}
