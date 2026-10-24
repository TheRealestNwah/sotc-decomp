extern void *GetScriptClass(unsigned char *);
extern void iosFree(int);
extern void isysDeleteSubThread(int);

void flushScriptObj(int arg0)
{
    int temp_v0_2;
    void *temp_v0;

    temp_v0 = GetScriptClass((unsigned char *)arg0);
    temp_v0_2 = (*(int *)((char *)(temp_v0) + 0x34));
    if (temp_v0_2 != 0) {
        iosFree(temp_v0_2);
    }
    if ((*(int *)((char *)(temp_v0) + 0)) != 0) {
        isysDeleteSubThread(arg0);
    }
}
