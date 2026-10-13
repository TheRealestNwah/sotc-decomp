int SpriteSetStatus(void *arg0, int arg1)
{
    float temp_f0;
    float temp_f0_2;
    float temp_f1;
    float var_f2;
    int var_v0;

    var_f2 = (*(float *)((char *)(arg0) + 8));
    temp_f1 = (*(float *)((char *)(arg0) + 0));
    var_v0 = arg1 + 1;
    if (temp_f1 < var_f2) {
        temp_f0 = var_f2 - 0.01f;
        var_f2 = temp_f1;
        (*(float *)((char *)(arg0) + 8)) = temp_f0;
        if (temp_f0 <= temp_f1) {
            (*(float *)((char *)(arg0) + 8)) = temp_f1;
            var_v0 = 0;
        } else {
            var_f2 = temp_f0;
        }
    }
    if (var_f2 < temp_f1) {
        temp_f0_2 = var_f2 + 0.01f;
        (*(float *)((char *)(arg0) + 8)) = temp_f0_2;
        if (temp_f1 <= temp_f0_2) {
            (*(float *)((char *)(arg0) + 8)) = temp_f1;
            var_v0 = 0;
        }
    }
    return var_v0;
}
