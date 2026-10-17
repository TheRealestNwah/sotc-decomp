typedef struct {
    int used;
    int current;
    unsigned char * flags;
    int width;
    void * data;
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
