typedef union {
    struct {
        float start;
        float end;
        float from;
        float to;
        float cur;
        int kind;
    } s;
    char alias;
} FadeParam;

extern FadeParam D_00179F00;
extern void setFadeParam(FadeParam *, int, float, float);

void setFade(float to, float time)
{
    setFadeParam(&D_00179F00, 27, to, time);
}
