extern int GAMEUTIL_destructor_record_info();

int CAM_destructor_target(int a, int b, int c, int d)
{
    return GAMEUTIL_destructor_record_info(a + 716, b, c, d);
}
