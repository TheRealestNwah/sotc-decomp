extern int GAMEUTIL_increase_yaw_limit_extend();

int GAMEUTIL_increase_yaw_limit(int a, int b, int c, int d)
{
    return GAMEUTIL_increase_yaw_limit_extend(a, 1, 1, b);
}
