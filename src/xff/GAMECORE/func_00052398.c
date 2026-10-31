extern char *GetScrLwsOriClass(void *);

static void func_00052398(void *obj)
{
    (*(int **)(GetScrLwsOriClass(obj) + 0x1208))[4] = 1;
}
