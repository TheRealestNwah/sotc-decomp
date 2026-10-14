struct FogFactorView {
    char pad00[4];
    float value04;
    float value08;
    float value0C;
    float value10;
    float value14;
};

extern struct FogFactorView B_00147398;

float getFogFactor1(void) {
    return (((B_00147398.value10 - B_00147398.value0C) *
             (B_00147398.value08 + B_00147398.value04) /
             (B_00147398.value08 - B_00147398.value04)) +
            (B_00147398.value10 + B_00147398.value0C)) *
           B_00147398.value14;
}
