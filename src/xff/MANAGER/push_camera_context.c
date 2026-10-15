extern int D_00139F3C;
extern void *B_0015D4B0[];
extern void SetVSMatrix(void *);

void push_camera_context(void *m)
{
    if (D_00139F3C < 31) {
        D_00139F3C++;
        B_0015D4B0[D_00139F3C] = m;
        SetVSMatrix(m);
    }
}
