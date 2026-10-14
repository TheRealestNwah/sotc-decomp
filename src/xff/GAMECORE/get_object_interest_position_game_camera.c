typedef int s128 __attribute__((mode(TI)));
int get_object_interest_position_game_camera(s128 *arg0, void *arg1) {
    if (((*(int *)((char *)(arg1) + 0x1360)) == 5) && ((*(int *)((char *)(arg1) + 0x3000)) == 1)) {
        *arg0 = (*(s128 *)((char *)(arg1) + 0x3050));
        return 1;
    }
    return 0;
}
