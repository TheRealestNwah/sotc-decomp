typedef struct {
    int used;
    int current;
    unsigned char *volatile flags;
    int width;
    void *volatile data;
} ModifiedManager;

void *RelocateModifiedManager(ModifiedManager *manager, int count, char *buffer)
{
    int width;
    char *end = buffer;
    if (count <= 65535) {
        width = count >= 256 ? 2 : 1;
    } else {
        width = 4;
    }
    if (count != 0) {
        manager->data = end;
        end += (width * count + 15) & ~15;
        manager->flags = (unsigned char *)end;
        end += (count + 15) & ~15;
    }
    return end;
}

void InitModifiedManager(ModifiedManager *manager, int count)
{
    int width;
    int i;
    manager->used = 0;
    manager->current = 0;
    if (count != 0) {
        width = count > 65535 ? 4 : (count >= 256 ? 2 : 1);
        manager->width = width;
        for (i = 0; i < count; i++) {
            manager->flags[i] = 0;
        }
    } else {
        manager->data = 0;
        manager->flags = 0;
    }
}
