typedef struct {
    char unknown00[0x38];
    float width;
    float height;
    float scaleU;
    float scaleV;
} Sprite;

extern float D_00136248[];
extern float D_00136258[];

static void func_00026C80(float *uv, Sprite *sprite, int cell)
{
    int column;
    int row;

    if (cell == -1)
        cell = 4;
    column = cell % 3;
    row = cell / 3;
    uv[0] = sprite->width * sprite->scaleU * D_00136248[column];
    uv[1] = sprite->height * sprite->scaleV * D_00136248[row];
    uv[2] = 1.0f;
    uv[3] = sprite->width * sprite->scaleU * D_00136258[column];
    uv[4] = sprite->height * sprite->scaleV * D_00136248[row];
    uv[5] = 1.0f;
    uv[6] = sprite->width * sprite->scaleU * D_00136248[column];
    uv[7] = sprite->height * sprite->scaleV * D_00136258[row];
    uv[8] = 1.0f;
    uv[9] = sprite->width * sprite->scaleU * D_00136258[column];
    uv[10] = sprite->height * sprite->scaleV * D_00136258[row];
    uv[11] = 1.0f;
}
