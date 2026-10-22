typedef struct {
    int used;
    int current;
    unsigned char * flags;
    int width;
    void * data;
} ModifiedManager;

extern void iosJumpRecoverPoint(const char *, ...);

void FlushModifiedManager(ModifiedManager *manager)
{
    int count = manager->used;
    int index;
    if (count != 0) {
        switch (manager->width) {
        case 1: {
            unsigned char *values = manager->data;
            for (index = 0; index < count; index++)
                manager->flags[*values++] = 0;
            break;
        }
        case 2: {
            unsigned short *values = manager->data;
            for (index = 0; index < count; index++)
                manager->flags[*values++] = 0;
            break;
        }
        case 4: {
            int *values = manager->data;
            for (index = 0; index < count; index++)
                manager->flags[*values++] = 0;
            break;
        }
        default:
            iosJumpRecoverPoint("modman:\tclear error:%d\n", manager->width);
            break;
        }
        manager->used = 0;
    }
}

int EntryModifiedManager(ModifiedManager *manager, int value)
{
    int index = manager->used++;
    switch (manager->width) {
    case 1:
        ((unsigned char *)manager->data)[index] = value;
        break;
    case 2:
        ((unsigned short *)manager->data)[index] = value;
        break;
    case 4:
        ((int *)manager->data)[index] = value;
        break;
    }
    manager->flags[value] = 1;
    return index;
}

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
