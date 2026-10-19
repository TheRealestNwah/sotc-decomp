typedef struct Node { int used; int a; struct Node *prev; struct Node *next; } Node;
extern Node *D_00136274;
extern int strcmp(const char *, const char *);

static inline char *textureName(char *object)
{
    char *texture = *(char **)(object + 0x20);
    int offset = 0;
    switch (*(int *)(texture + 0x1C) & 0x3F) {
    case 0x13:
    case 0x1B:
        offset = 0x400;
        break;
    case 0x14:
    case 0x24:
    case 0x2C:
        offset = 0x40;
        break;
    }
    return texture + *(int *)(texture + 0x18) + offset;
}

static inline void *findTexture(void *namePointer)
{
    const char *name = namePointer;
    Node *node = D_00136274;
    char *result = 0;
    for (; node; node = node->next) {
        char *object = *(char **)((char *)node->a + 0x28);
        if (strcmp(name, textureName(object)) == 0) {
            result = object;
            break;
        }
    }
    return result;
}

extern void texScaleClut(void *, float *);
void texScaleClutByName(void *name, float *scale)
{
    void *object = findTexture(name);
    if (object)
        texScaleClut(object, scale);
}
