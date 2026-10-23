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
int GetCharacterClassInitParamNbNodes(CharacterClass *c)
{
    if (!c->init) { return c->nbNodes; }
    return c->init->param->nbNodes;
}
