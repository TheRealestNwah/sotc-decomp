extern int getDrawScreenWidth(void);
extern int getDrawScreenHeight(void);
extern void iosDlPushLayer(int);
extern void iosDlPopLayer(void);
extern void gsRegBegin(void);
extern void gsReg(int, unsigned long);
extern void gsRegEnd(void);

#define SET_XYZ(x, y, z) ((unsigned long)(x) | ((unsigned long)(y) << 16) | ((unsigned long)(z) << 32))
#define SET_RGBAQ(r, g, b, a, q) ((unsigned long)(r) | ((unsigned long)(g) << 8) | ((unsigned long)(b) << 16) | ((unsigned long)(a) << 24) | ((unsigned long)(q) << 32))

static void func_000C95C0(float alpha)
{
    int a = alpha * 64.0f;
    int x = -getDrawScreenWidth() / 2;
    int y = -getDrawScreenHeight() / 2;
    int x1 = -x;

    iosDlPushLayer(0x19);
    gsRegBegin();
    gsReg(0x47, 0x31001);
    gsReg(0x42, 0x8000000044);
    gsReg(0, 0x4C);
    gsReg(1, SET_RGBAQ(0, 0, 0, a, 0x3F800000));
    gsReg(4, SET_XYZ((x + 0x800) << 4, (y + 0x800) << 4, 0xFFFE524F));
    gsReg(4, SET_XYZ((x1 + 0x800) << 4, (y + 0x800) << 4, 0xFFFE524F));
    gsReg(1, SET_RGBAQ(0, 0, 0, 0, 0x3F800000));
    gsReg(4, SET_XYZ((x + 0x800) << 4, (y + 0x80 + 0x800) << 4, 0xFFFE524F));
    gsReg(4, SET_XYZ((x1 + 0x800) << 4, (y + 0x80 + 0x800) << 4, 0xFFFE524F));
    gsRegEnd();
    iosDlPopLayer();
}
