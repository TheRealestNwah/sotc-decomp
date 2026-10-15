extern void glColor4f(float, float, float, float);
extern void DebugDispRadiusIndicator(void *, float, int);

void DebugDispPosition(void *pos, float r)
{
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    DebugDispRadiusIndicator(pos, r, 1);
}
