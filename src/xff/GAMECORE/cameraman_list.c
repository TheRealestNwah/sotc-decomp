extern void *B_0019FD28[];
extern void *get_camera_obj(void *);
typedef struct { int a; int n; int man[5]; } CameraMen;
extern CameraMen B_0019FD20;
extern int B_0019FD24;

static void func_000E36C0(void);

void *get_cameraman(int i)
{
    ((void (*)(int))func_000E36C0)(i);
    return B_0019FD28[i];
}

void *get_cameraman_camera_obj(int i)
{
    ((void (*)(int))func_000E36C0)(i);
    return get_camera_obj(B_0019FD28[i]);
}

int employ_cameraman(void *m)
{
    int i;
    for (i = 0; i < 5; i++) {
        if (B_0019FD20.man[i] == 0) {
            B_0019FD20.man[i] = (int)m;
            B_0019FD20.n++;
            return i;
        }
    }
    __asm__ __volatile__("break 0");
    return -1;
}

void change_main_cameraman(int arg0)
{
    ((void (*)())func_000E36C0)();
    (*(int *)&B_0019FD20) = arg0;
}

int get_main_cameraman_id(void)
{
    return (*(int *)&B_0019FD20);
}

int is_main_cameraman_exist(void)
{
    return ~(*(int *)&B_0019FD20) != 0;
}

int get_total_cameraman(void)
{
    return B_0019FD24;
}

int get_max_cameraman(void)
{
    return 5;
}

static void func_000E36C0(void)
{
}
