void GetMeshObjInfo(void *arg0, int arg1, int arg2)
{
    int var_a2;
    int var_a3;

    var_a2 = arg2;
    var_a3 = 1;
    if (arg1 < var_a2) {
        do {
            var_a2 = (var_a2 - arg1) + 2;
            var_a3 += 1;
        } while (arg1 < var_a2);
    }
    (*(int *)((char *)(arg0) + 4)) = var_a3;
    (*(int *)((char *)(arg0) + 0)) = 0;
}
