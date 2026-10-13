int is_letter_reach_time(void *arg0, float fparg0)
{
    float temp_f1;
    int var_v0;

    temp_f1 = (*(float *)((char *)(arg0) + 8));
    var_v0 = 1;
    if (!((*(float *)((char *)(arg0) + 4)) <= temp_f1)) {
        var_v0 = 0;
        (*(float *)((char *)(arg0) + 8)) = (float) (temp_f1 + fparg0);
    }
    return var_v0;
}
