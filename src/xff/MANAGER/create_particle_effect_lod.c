extern void *malloc_from_root_partition(int, const char *);
extern void iosUnitMatrix(void *);

void *create_particle_effect_lod(void)
{
    /* EUC-JP "パーティクルLOD" (particle LOD) */
    char *p = malloc_from_root_partition(0x140, "\xA5\xD1\xA1\xBC\xA5\xC6\xA5\xA3\xA5\xAF\xA5\xEB" "LOD");
    *(int *)(p + 0xD0) = 0;
    *(int *)(p + 0xD4) = 0;
    *(int *)(p + 0xD8) = 0;
    *(int *)(p + 0xDC) = 0;
    iosUnitMatrix(p + 0xE0);
    return p;
}
