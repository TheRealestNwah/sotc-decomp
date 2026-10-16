extern void *GetCollisionDBPlane(void *);
extern void iosApplyRotMatrix(void *, void *, void *);
extern float GetPlaneSlopeDegree(void *);

int moveCtrlWallJudgeFunc(void *col, char *w)
{
    float plane[4];

    iosApplyRotMatrix(plane, w, GetCollisionDBPlane(col));
    if (__builtin_fabsf(GetPlaneSlopeDegree(plane)) <= *(float *)(w + 0x40))
        return 0;
    return 1;
}
