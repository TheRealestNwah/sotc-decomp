extern char *GetSCRCharaAIWorkPtr(void *);
extern void deleteUserPathWork(char *);

static void func_00056550(void *obj)
{
    deleteUserPathWork(GetSCRCharaAIWorkPtr(obj) + 0x10);
}
