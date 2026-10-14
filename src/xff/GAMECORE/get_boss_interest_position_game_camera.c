typedef int s128 __attribute__((mode(TI)));
int get_boss_interest_position_game_camera(s128 *arg0, void *arg1) {
    if (((*(int *)((char *)(arg1) + 0x1360)) == 4) && ((*(int *)((char *)(arg1) + 0x2EE0)) == 1)) {
        *arg0 = (*(s128 *)((char *)(arg1) + 0x2F30));
        return 1;
    }
    return 0;
}
