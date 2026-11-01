typedef int Qword __attribute__((mode(TI)));
typedef struct { Qword quat; Qword pos; } QuatPos;

static inline void copyQuatPosByValue(QuatPos dst, QuatPos src)
{
    dst.quat = src.quat;
    dst.pos = src.pos;
}

void CopyQuatPos(QuatPos *dst, QuatPos *src)
{
    copyQuatPosByValue(*dst, *src);
}
