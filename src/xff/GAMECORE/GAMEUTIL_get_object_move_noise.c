extern int GAMEUTIL_is_horse_obj_contact_ground(int *, void *);
extern int GAMEUTIL_get_horse_move_status(int, int);

float GAMEUTIL_get_object_move_noise(void *o)
{
    int st = 0;
    int c = GAMEUTIL_is_horse_obj_contact_ground(&st, o);
    float f = 0.5f;
    if (c == 1) {
        f = 0.3f;
        if (GAMEUTIL_get_horse_move_status(0, st) != c)
            f = 1.0f;
    }
    return f;
}
