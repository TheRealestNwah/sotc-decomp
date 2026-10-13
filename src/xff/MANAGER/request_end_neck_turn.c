void request_end_neck_turn(void *arg0)
{
    if ((*(int *)((char *)(arg0) + 0x30)) != 0) {
        (*(int *)((char *)(arg0) + 0x34)) = 1;
        return;
    }
    (*(int *)((char *)(arg0) + 0x34)) = 0;
}
