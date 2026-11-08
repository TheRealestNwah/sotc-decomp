extern float getRatioFromInterp(float, float);
extern float fabsf(float);

#ifdef NONMATCHING
float calcMoveAngle(float *out, float target, float cur, float time, float goal)
{
    float ratio;
    float sum;
    float cnt;

    ratio = getRatioFromInterp(time, 0.033333335f);
    sum = 0.0f;
    cnt = 0.0f;
    if (time >= 0.033333335f && fabsf(target - cur) > 0.017453293f) {
        cnt = 0.033333335f;
        sum = cur * 0.033333335f + 0.0f;
        if (!(fabsf(sum + goal) <= 0.017453293f)) {
            do {
                cur = target * ratio + cur * (1.0f - ratio);
                if (!(fabsf(target - cur) > 0.017453293f)) {
                    break;
                }
                cnt += 0.033333335f;
                sum += cur * 0.033333335f;
            } while (!(fabsf(sum + goal) <= 0.017453293f));
        }
    }
    if (out != 0) {
        *out = cnt;
    }
    return sum;
}
#else
extern float calcMoveAngle(float *out, float target, float cur, float time, float goal);
#endif
