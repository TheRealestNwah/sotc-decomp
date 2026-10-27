extern void triangleDispSetup(void);
extern void trianglePolyColor(int, float, float, float, float);
static void func_000A6240(void *, int, float, float, float, float, float, float, int, float);

void DebugDispCollisionDB(void *db, int flags)
{
    triangleDispSetup();
    trianglePolyColor(1, -1.0f, -1.0f, -1.0f, -1.0f);
    func_000A6240(db, flags, 0.6f, 0.8f, 1.0f, 1.0f, 0.7f, 0.5f, -1, 0.2f);
}
