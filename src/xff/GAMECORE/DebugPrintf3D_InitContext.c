extern void iosInitKPrintfContext3D(int, int, int, int, float, float, float, float);

void DebugPrintf3D_InitContext(int a, int b)
{
    iosInitKPrintfContext3D(a, b, 0, 1, 0.5f, 0.75f, 1.0f, 1.0f);
}
