typedef struct {
    char pad0[0x110];
    unsigned int flags;
    char pad114[0xC];
    int directional_count;
    int total_count;
} GlobalLight;

int globalLightCalcLightNum(GlobalLight *light, int type)
{
    int slot = 4;
    switch (type) {
    case 0x19:
        slot = 3;
        light->flags |= 4;
        light->total_count = light->directional_count + 1;
        break;
    case 0x1A:
        switch (light->directional_count) {
        case 0: slot = 0; light->flags |= 8; break;
        case 1: slot = 1; light->flags |= 0x10; break;
        case 2: slot = 2; light->flags |= 0x20; break;
        }
        if (slot != 4) {
            light->directional_count++;
            light->total_count++;
        }
        break;
    }
    return slot;
}
