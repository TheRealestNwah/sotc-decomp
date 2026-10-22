extern int GAMEUTIL_is_horse_obj(void *);
extern void GAMEUTIL_get_horse_move_status(unsigned int *, void *);

int CAM_is_target_fast_moving(char *camera)
{
    void *target;

    if (*(void **)(camera + 0x2C8) != 0)
        target = *(void **)(camera + 0x2C8);
    else
        target = *(void **)camera;
    if (GAMEUTIL_is_horse_obj(target) == 1) {
        unsigned int status = 0;
        GAMEUTIL_get_horse_move_status(&status, target);
        switch (status) {
        case 3:
        case 4:
            return 1;
        }
        return 0;
    }
    return (*(unsigned int *)(camera + 0x178) >> 4) & 1;
}
