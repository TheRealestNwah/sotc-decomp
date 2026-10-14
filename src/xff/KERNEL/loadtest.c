extern int func_00008BB0(int, int, int);
extern int iosLoaderGetFileSizeName();

int loadtest(int arg0, int arg1)
{
    int temp_v0;
    int var_v1;

    temp_v0 = iosLoaderGetFileSizeName();
    var_v1 = 0;
    if (temp_v0 >= 0) {
        var_v1 = func_00008BB0(arg0, temp_v0, arg1);
    }
    return var_v1;
}
