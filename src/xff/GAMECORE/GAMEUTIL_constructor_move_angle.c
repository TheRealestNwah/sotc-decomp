extern void GAMEUTIL_reset_move_angle(int *);

void GAMEUTIL_constructor_move_angle(void *work)
{
    GAMEUTIL_reset_move_angle((int *)work);
    {
        float limit = 1.0471975f;
        float weight = 0.8f;
        float speed = 1.74532926f;
        float step = 0.0174532925f;
        float angle = 0.87266463f;

        /* These stores retain the original order under ee-gcc 2.96. */
        *(volatile float *)((char *)work + 8) = limit;
        *(float *)((char *)work + 0x18) = step;
        *(volatile float *)((char *)work + 0xC) = angle;
        *(float *)((char *)work + 0x10) = weight;
        *(float *)((char *)work + 0x14) = speed;
        *(volatile float *)((char *)work + 4) = angle;
    }
}
