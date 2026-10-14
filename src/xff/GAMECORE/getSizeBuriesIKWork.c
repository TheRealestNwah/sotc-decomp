extern int GetCharacterClassInitParamNbOptionNodes();
extern void iosJumpRecoverPoint(void *);
extern unsigned char RO_00181760[1];

int getSizeBuriesIKWork(void)
{
    int temp_v0;

    temp_v0 = GetCharacterClassInitParamNbOptionNodes();
    if (temp_v0 < 0) {
        iosJumpRecoverPoint(&RO_00181760);
        return 0;
    }
    return (temp_v0 << 5) + 0x10;
}
