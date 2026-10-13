extern int GetCharacterClassInitParamNbOptionNodes();

int getPinAttackIKWorkSize(void)
{
    return GetCharacterClassInitParamNbOptionNodes() << 6;
}
