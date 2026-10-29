typedef struct {
    char pad0[4];
    int nbNodes;
    char pad8[0x18];
    int nbOptionNodes;
} InitParam;

typedef struct {
    char pad0[0x20];
    InitParam *param;
} InitParamHolder;

typedef struct {
    char pad0[4];
    int nbNodes;
    char pad8[0x84 - 8];
    InitParamHolder *init;
} CharacterClass;

extern int GetCharacterClassInitParamNbOptionNodes(CharacterClass *);
extern void iosJumpRecoverPoint(void *);
extern unsigned char RO_00181760[];

int getSizeBuriesIKWork(CharacterClass *character)
{
    int temp_v0;

    temp_v0 = GetCharacterClassInitParamNbOptionNodes(character);
    if (temp_v0 < 0) {
        iosJumpRecoverPoint(RO_00181760);
        return 0;
    }
    return (temp_v0 << 5) + 0x10;
}
