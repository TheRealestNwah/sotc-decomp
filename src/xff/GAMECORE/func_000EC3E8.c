extern char *GetLayoutClass(void *);
extern void CAM_init_aim_angle_rot(void *, int);

static int func_000EC3E8(void *obj)
{
    if (obj != 0) {
        return *(int *)(GetLayoutClass(obj) + 0x1AC);
    }
    return 1000000;
}

static void func_000EC420(void)
{
}

static void func_000EC428(void *unused, char *c)
{
    CAM_init_aim_angle_rot(c + 0x4, 0);
    CAM_init_aim_angle_rot(c + 0x48, 1);
    CAM_init_aim_angle_rot(c + 0x8C, 1);
    *(int *)(c + 0xD0) = 0;
}

static void func_000EC470(void *unused, char *c)
{
    *(int *)(c + 0x94) = 0;
    *(int *)(c + 0x98) = 0;
}

static void func_000EC480(void)
{
}

static void func_000EC488(void)
{
}
