extern void glColor4f(float, float, float, float);
extern void DebugDispRadiusIndicator(void *, int, float);

void DebugDispPositionColor(void *pos, float *color, float radius)
{
    glColor4f(color[0], color[1], color[2], color[3]);
    DebugDispRadiusIndicator(pos, 1, radius);
}
