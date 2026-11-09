/* Parked: 2 words off (0x64 lands in $v0 instead of $v1). The inline_fn helper is what fixes the constant scheduling. */
#ifdef NONMATCHING

extern int getDrawScreenHeight(void);
extern int getDrawScreenWidth(void);
extern void gsReg(int, long);
extern void gsRegBegin(void);
extern void gsRegEnd(void);
extern void iosDlPopLayer(void);
extern void iosDlPushLayer(int);
inline int inline_fn(int arg0, int arg1)
{
  return arg0 + arg1;
}

void drawDemoBar(int arg0, int arg1, float alpha)
{
  int w = getDrawScreenWidth();
  int h = getDrawScreenHeight() >> 1;
  int a = (int) (alpha * 128.0f);
  int hw = w >> 1;
  if (a != 0)
  {
    long m;
    int x0;
    int x1;
    iosDlPushLayer(arg0);
    gsRegBegin();
    gsReg(0x42, (((long) a) << 0x20) | 0x64);
    gsReg(0x47, 0x31001);
    m = -1L;
    m = m << 0x20;
    gsReg(0x49, 0);
    gsReg(0, 0x146);
    gsReg(1, ((0x3F800000L << 0x10) | 0x8000) << 0x10);
    x0 = (0x800 - hw) * 0x10;
    gsReg(4, (x0 | (((long) ((0x800 - h) * 0x10)) << 0x10)) | m);
    x1 = inline_fn(hw, 0x800) * 0x10;
    gsReg(4, (x1 | (((long) (inline_fn(arg1 - h, 0x800) * 0x10)) << 0x10)) | m);
    gsReg(4, (x0 | (((long) (inline_fn(h - arg1, 0x800) * 0x10)) << 0x10)) | m);
    gsReg(4, (x1 | (((long) (inline_fn(h, 0x800) * 0x10)) << 0x10)) | m);
    gsReg(0x42, (0x80L << 0x20) | 0x44);
    gsReg(0x47, 0x5100D);
    gsReg(0x49, 1);
    gsReg(1, (((0x3F800000L << 0x10) | 0x80FF) << 0x10) | 0xFFFF);
    gsRegEnd();
    iosDlPopLayer();
  }
}
#else
extern void drawDemoBar(int, int, float);
#endif
