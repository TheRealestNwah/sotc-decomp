extern void triangleDispSetup(void);
extern void trianglePolyColor(int, float, float, float, float);
static void func_000A6240(void *, int, float, float, float, float, float, float, int, float);

void DebugDispCollisionDBColor(void *db, float r, float g, float b, float a)
{
    triangleDispSetup();
    trianglePolyColor(1, -1.0f, -1.0f, -1.0f, -1.0f);
    func_000A6240(db, 0, r, g, b, r, g, b, -1, a);
}
