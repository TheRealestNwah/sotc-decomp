extern int end_camera_lws_animation(int);
extern void isysDeleteGroupAllObj(void *);

static void func_00011448(void *unused, int *w)
{
    int anim;
    int *p;

    w[13] = 0;
    anim = w[11];
    p = &w[11];
    if (anim >= 0) {
        end_camera_lws_animation(w[11]);
        *p = -1;
    }
    isysDeleteGroupAllObj(w);
}
