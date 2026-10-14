extern float func_000E95C8(float, int);
extern void func_000E9640(void *, float);
extern void func_000E9730(void *);
extern void func_000E9780(void *, float);

void update_clip_screen(void *screen)
{
    float value;

    value = func_000E95C8(*(float *)((char *)screen + 0xC),
                         *(int *)((char *)screen + 4));
    func_000E9640(screen, value);
    func_000E9730(screen);
    func_000E9780(screen, value);
}
