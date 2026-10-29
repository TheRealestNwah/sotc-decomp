typedef struct { float ordinary, boss; } CameraKeepParameters;
extern int GAMEUTIL_is_boss_obj(void *, int);
static float func_000D5CA8(void *object, CameraKeepParameters *parameters)
{
    float ordinary = parameters->ordinary;
    float boss = parameters->boss;
    return GAMEUTIL_is_boss_obj(object, 1) == 1 ? boss : ordinary;
}
