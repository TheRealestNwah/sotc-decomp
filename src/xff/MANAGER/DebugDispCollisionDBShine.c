extern void triangleDispSetup(void);
extern void trianglePolyColor(int, float, float, float, float);
static void func_000A6240(void *, int, float, float, float, float, float, float, int, float);

void DebugDispCollisionDBShine(void *db, float f)
{
    triangleDispSetup();
    trianglePolyColor(1, -1.0f, -1.0f, -1.0f, -1.0f);
    func_000A6240(db, 0, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1, f);
}
