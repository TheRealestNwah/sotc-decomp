extern int D_0017B870;
extern char B_001A5A50[];
extern void glColor4f(float, float, float, float);
extern void DebugDispRadiusIndicator(void *, float, int);

void drawGazeTool(void)
{
    if (D_0017B870 != 0) {
        glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
        DebugDispRadiusIndicator(B_001A5A50, 0.5f, 5);
    }
}
