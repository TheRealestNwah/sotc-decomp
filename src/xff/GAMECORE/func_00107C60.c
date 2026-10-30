extern int DEBUG_is_locking_debug_camera(void);
extern int DebugGlobalMoveWith2ndController(float *out, float *in);
extern float B_001A5A50[];

static void func_00107C60(void)
{
    if (DEBUG_is_locking_debug_camera()) {
        DebugGlobalMoveWith2ndController(B_001A5A50, B_001A5A50);
    }
}
