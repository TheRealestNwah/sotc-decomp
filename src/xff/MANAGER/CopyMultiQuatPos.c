typedef int Qword __attribute__((mode(TI)));
typedef struct { Qword quat; Qword pos; } QuatPos;

static inline void copyQuatPosByValue(QuatPos dst, QuatPos src)
{
    dst.quat = src.quat;
    dst.pos = src.pos;
}

void CopyMultiQuatPos(QuatPos *dst, QuatPos *src, int n)
{
    int i;
    for (i = 0; i < n; i++)
        copyQuatPosByValue(dst[i], src[i]);
}
