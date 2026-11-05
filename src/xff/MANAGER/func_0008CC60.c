extern void iosDlPushLayer(int);
extern void iosDlPopLayer(void);
extern void glColor4f(float, float, float, float);
extern void glBegin(int);
extern void glEnd(void);
extern void glBlendFunc(int, int);
extern void glVertex3f(float, float, float);
extern void func_0008C5C0(int, float, float, float, float);
extern void func_0008C988(int, float, float, float, float);

/* 0x1.41b2f4p-2f is pi / 10, rounded the way the original data has it. */
static void func_0008CC60(void *a0, void *a1, void *a2, float *size, float *color)
{
    iosDlPushLayer(0x17);
    glColor4f(color[0], color[1], color[2], color[3]);
    glBegin(8);
    glBlendFunc(5, 6);
    glEnd();
    glBegin(1);
    glVertex3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, size[0]);
    glEnd();
    func_0008C5C0(2, size[1] * 0.5f, 1.0f, 0x1.41b2f4p-2f, 1.0f);
    func_0008C5C0(2, size[1] * 0.5f, size[0], 0x1.41b2f4p-2f, 1.0f);
    func_0008C988(2, 1.0f, size[0], size[1] * 0.5f, 1.0f);
    func_0008C988(2, 1.0f, size[0], size[1] * 0.5f, -1.0f);
    iosDlPopLayer();
}
