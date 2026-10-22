typedef struct {
    unsigned long lower : 40;
    unsigned long mode : 4;
    unsigned long source : 2;
    unsigned long destination : 2;
    unsigned long upper : 16;
} SpriteFlags;
typedef struct {
    char pad[0x48];
    SpriteFlags flags;
} Sprite;
void spriteSetBlendMode(Sprite *sprite, unsigned int mode, unsigned int source, unsigned int destination)
{
    sprite->flags.mode = mode;
    sprite->flags.source = source;
    sprite->flags.destination = destination;
}

