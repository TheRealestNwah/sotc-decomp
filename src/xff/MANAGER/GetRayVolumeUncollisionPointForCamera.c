extern char objfilter[];
extern int func_000A80F0();
extern int GetRayVolumeUncollisionPoint(int, int, int, int, int, void *, int, int, void *, int);

int GetRayVolumeUncollisionPointForCamera(int a, int b, int c, int d, int e, int f)
{
    return GetRayVolumeUncollisionPoint(a, b, c, d, e, objfilter, 0, 0, func_000A80F0, f);
}
