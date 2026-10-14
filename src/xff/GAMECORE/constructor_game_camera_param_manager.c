extern void func_000ED5D8(void *);

void constructor_game_camera_param_manager(void *arg0)
{
    (*(int *)((char *)(arg0) + 0)) = 0;
    (*(int *)((char *)(arg0) + 4)) = 0;
    (*(int *)((char *)(arg0) + 8)) = 0;
    (*(int *)((char *)(arg0) + 0xC)) = 0;
    func_000ED5D8(arg0 + 0x10);
    func_000ED5D8(arg0 + 0x664);
    func_000ED5D8(arg0 + 0xCB8);
    (*(int *)((char *)(arg0) + 0x130C)) = 0;
}
