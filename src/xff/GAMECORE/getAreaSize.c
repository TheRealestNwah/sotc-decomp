struct AreaSizeView {
    char pad00[0x38];
    int integer_factor;
    char pad3C[4];
    volatile float float_factor;
};

extern struct AreaSizeView D_0017A340;

float getAreaSize(void)
{
    float integer_factor = (float)D_0017A340.integer_factor;
    float float_factor = D_0017A340.float_factor;
    return float_factor * integer_factor;
}
