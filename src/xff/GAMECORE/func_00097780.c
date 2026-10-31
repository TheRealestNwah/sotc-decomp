extern char *GetSCRCharaAIWorkPtr(void *);
extern void deleteUserPathWork(char *);

static void func_00097780(void *obj)
{
    deleteUserPathWork(GetSCRCharaAIWorkPtr(obj) + 0x10);
}
