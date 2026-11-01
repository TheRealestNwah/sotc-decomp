extern void *B_0015E350[];
extern void disp_camera_region(void *, float, int, int);

void disp_object_animation_camera_region_group(int mode, int arg)
{
    int i;
    int j;
    int flag;
    float alpha;

    for (i = 0; i < 2; i++) {
        if (i != 0 && mode != 1)
            continue;
        flag = 1;
        alpha = 1.0f;
        if (i == 1) {
            alpha = 0.2f;
            flag = 0;
        }
        for (j = 0; j < 50; j++) {
            if (B_0015E350[j])
                disp_camera_region(B_0015E350[j], alpha, flag, arg);
        }
    }
}
