extern void create_original_view_matrix(int, int, int, int);
extern void func_000E7930(void *);
extern void update_clip_screen(int);
extern void update_transform_matrix_set(int, void *, int);

void update_camera_obj(void *arg0)
{
    create_original_view_matrix(arg0 + 0x210, arg0 + 0x1E0, arg0 + 0x1F0, arg0 + 0x200);
    update_clip_screen((*(int *)((char *)(arg0) + 0x250)));
    update_transform_matrix_set((*(int *)((char *)(arg0) + 0x254)), arg0, (*(int *)((char *)(arg0) + 0x250)));
    func_000E7930(arg0);
}
