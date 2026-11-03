typedef struct { char pad[0x80]; int x80; } Demo;
extern void setDemoBar(float, float);
extern void gameModeCls(int);
extern void gameModeSet(int);
extern void *CAM_get_target_obj(void *);
extern void nico_playerSetAttentionHeadActFlag(void *, int);
extern void func_000E95E0(void *);
static void func_000EC540(char *cam, Demo *d)
{
    setDemoBar(0.0f, 2.0f);
    while (d->x80 != 0) {
        if (d->x80 > 0) {
            gameModeCls(1);
            d->x80 = d->x80 - 1;
        } else {
            gameModeSet(1);
            d->x80 = d->x80 + 1;
        }
    }
    nico_playerSetAttentionHeadActFlag(CAM_get_target_obj(cam + 0x23C), 0);
    func_000E95E0(d);
}
