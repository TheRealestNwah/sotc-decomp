typedef int s128 __attribute__((mode(TI)));

typedef union {
    s128 q;
    float f[4];
    int i[4];
} Vec4;

typedef struct {
    Vec4 vectors[5];
    int type;
    float values[3];
} JudgeVolume;

void SetJudgeVolumeInfo(int address, int type, int vector0, int vector1,
                       float *vector4, float *vector2, float *vector3,
                       float x, float y, float z)
{
    JudgeVolume *volume = (JudgeVolume *)address;

    volume->type = type;
    volume->vectors[0].q = ((Vec4 *)vector0)->q;
    volume->vectors[1].q = ((Vec4 *)vector1)->q;
    volume->vectors[4].q = ((Vec4 *)vector4)->q;
    volume->vectors[2].q = ((Vec4 *)vector2)->q;
    volume->vectors[3].q = ((Vec4 *)vector3)->q;
    volume->values[0] = x;
    volume->values[1] = y;
    volume->values[2] = z;
}
