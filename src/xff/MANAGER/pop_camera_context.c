extern int D_00139F3C;
extern void *B_0015D4B0[];
extern void SetVSMatrix(void *);

void pop_camera_context(void)
{
    if (D_00139F3C > 0) {
        D_00139F3C--;
        SetVSMatrix(B_0015D4B0[D_00139F3C]);
    }
}
