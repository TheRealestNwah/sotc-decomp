void request_end_motion_ik_interest(int *p)
{
    int v = p[1];

    if (v != 1) {
        v = 0;
    }
    p[2] = v;
}
