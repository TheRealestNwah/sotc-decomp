typedef int s128 __attribute__((mode(TI)));

typedef union {
    s128 q;
    float f[4];
    int i[4];
} Vec4;

typedef struct {
    char pad[0x30];
    int value30;
    char pad34[0xC];
} OptionNode;

typedef struct {
    char pad[0x24];
    OptionNode *nodes;
} OptionContext;

typedef struct {
    char pad[0x2EC];
    Vec4 *quaternions;
    Vec4 *positions;
    char pad2F4[0x64];
    OptionContext *options;
} CharacterClass;

int GetCharacterClassOptionNodeLocalQuaternionPos(Vec4 *quaternion, Vec4 *position,
                                                 CharacterClass *character, int index)
{
    OptionNode *node = &character->options->nodes[index];
    s128 positionValue = character->positions[index].q;
    int value = node->value30;

    position->q = positionValue;
    quaternion->q = character->quaternions[index].q;
    return value;
}
