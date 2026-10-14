struct CameraSelectionView {
    int selected;
    char pad04[4];
    void *managers[0];
};

extern void *get_camera_obj(void *);
extern struct CameraSelectionView B_0019FD20;

void *get_main_cameraman_camera_obj(void)
{
    return get_camera_obj(B_0019FD20.managers[B_0019FD20.selected]);
}
