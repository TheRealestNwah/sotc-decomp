extern char B_000E2210[];

int vab_get_semastervol(int id)
{
    return *(int *)(B_000E2210 + id * 0x2C);
}
