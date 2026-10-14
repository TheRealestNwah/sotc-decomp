extern int GetGeoDispClass();

int get_top_emitter_list_from_particle_geodisp(int arg0)
{
    if (arg0 != 0) {
        return GetGeoDispClass() + 0xE8;
    }
    return 0;
}
