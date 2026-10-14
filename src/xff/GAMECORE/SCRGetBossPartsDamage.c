float SCRGetBossPartsDamage(void *context, int part_id)
{
    char *part;
    int count;
    int offset;
    int index;

    count = *(int *)((char *)context + 0x54);
    index = 0;
    if (count > 0) {
        part = *(char **)((char *)context + 0x10);
        offset = 0x20;
        do {
            int id = *(int *)part;
            part += 0x58;
            if (part_id == id) {
                return *(float *)((*(int *)((char *)context + 0xE8) + offset) + 4);
            }
            index++;
            offset += 8;
        } while (index < count);
    }
    return -1.0f;
}
