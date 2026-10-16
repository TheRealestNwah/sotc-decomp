extern void func_000E1C38(void *, void *);
extern void func_000E1CF0(void *, void *, float);
extern void func_000E1D58(void *, void *, float, float, float);
extern void func_000E1E48(void *, void *, float, float);

void CAM_doit_camera_warp_cntrl(void *a, void *b, float p, float q, float r, float t)
{
    func_000E1C38(a, b);
    func_000E1CF0(a, b, t);
    func_000E1D58(a, b, p, q, t);
    func_000E1E48(a, b, r, t);
}
