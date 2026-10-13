extern void isysSleepSubThread();

void isysSleepSubThreadM(int arg0)
{
    int var_s0;

    if (arg0 > 0) {
        var_s0 = arg0;
        do {
            var_s0 -= 1;
            isysSleepSubThread();
        } while (var_s0 != 0);
    }
}
