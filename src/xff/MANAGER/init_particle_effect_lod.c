typedef union { int i; float f; char *p; } WorkWord;
extern void get_polygon_scale_rotation_matrix(void *);
extern float get_radiate_range_coefficient(float);
void init_particle_effect_lod(char *effect)
{
    int width, height, tiles;
    int index, offset;
    char *particle;
    if (effect) {
        get_polygon_scale_rotation_matrix(effect);
        width = ((WorkWord *)(effect + 0x7C))->i;
        height = ((WorkWord *)(effect + 0x80))->i;
        tiles = width * height;
        ((WorkWord *)(effect + 0x120))->i = tiles;
        if (tiles < 2) {
            ((WorkWord *)(effect + 0x124))->f = 1.0f;
            ((WorkWord *)(effect + 0x128))->f = 1.0f;
            ((WorkWord *)(effect + 0x12C))->f = 1.0f;
            ((WorkWord *)(effect + 0x130))->f = 1.0f;
        } else {
            ((WorkWord *)(effect + 0x124))->f = (float)tiles;
            ((WorkWord *)(effect + 0x128))->f = (float)width;
            ((WorkWord *)(effect + 0x12C))->f = 1.0f / (float)width;
            ((WorkWord *)(effect + 0x130))->f = 1.0f / (float)height;
        }
        if (((WorkWord *)(effect + 0x50))->f > ((WorkWord *)(effect + 0x54))->f)
            ((WorkWord *)(effect + 0x134))->f = ((WorkWord *)(effect + 0x50))->f;
        else
            ((WorkWord *)(effect + 0x134))->f = ((WorkWord *)(effect + 0x54))->f;
        index = 0;
        ((WorkWord *)(effect + 0x134))->f *= 0.5f;
        if (((WorkWord *)(effect + 0xD0))->i > 0) {
            offset = 0;
            do {
                particle = *(char **)(effect + 0xD4) + offset;
                ++index;
                offset += 0x1BC;
                ((WorkWord *)(particle + 0x1B8))->f = get_radiate_range_coefficient(((WorkWord *)(particle + 0x18))->f);
            } while (index < ((WorkWord *)(effect + 0xD0))->i);
        }
    }
}
