typedef struct {
    char pad[8];
    unsigned int status : 4;
    unsigned int rest : 28;
    char pad2[0x38];
} SpriteMenuLayer;

static void func_00098948(void *);

void SpriteMenuSetDispFlagAll(unsigned char *o, int disp)
{
    unsigned char *c = o[8] == 0x21 ? o + 0x90 : 0;
    SpriteMenuLayer *e = *(SpriteMenuLayer **)(c + 4);
    int i;

    for (i = 0; i < *(int *)(c + 8); i++, e++) {
        if (disp) {
            switch (e->status) {
            case 0:
            case 4:
            case 5:
                e->status = 1;
                func_00098948(e);
                break;
            }
        } else {
            switch (e->status) {
            case 1:
            case 2:
            case 3:
                e->status = 4;
                func_00098948(e);
                break;
            }
        }
    }
}
