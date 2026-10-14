extern void func_000E36C0(int);
extern void *B_0019FD28[];
extern void *get_camera_obj(void *);

void *get_cameraman_camera_obj(int i)
{
    func_000E36C0(i);
    return get_camera_obj(B_0019FD28[i]);
}
