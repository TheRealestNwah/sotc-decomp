extern const float RO_0018163C;
extern void *getSCRDataCtrlWork(void);
extern void setSearchRadius(char *w, float radius);

static inline float fsqrt(float x)
{
    float r;

    __asm__ __volatile__("sqrt.s %0, %1" : "=f"(r) : "f"(x));
    return r;
}

void SCRFuncResetSearchRadius(void)
{
    setSearchRadius(getSCRDataCtrlWork(), fsqrt(RO_0018163C));
}
