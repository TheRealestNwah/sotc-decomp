typedef struct {
    int work[2];
    int adrs[2];
    int ptr;
    int layer_num;
    int cur;
    int pad1C;
    int grp[2];
    int lock[2];
} DlBufs;
extern DlBufs B_00065018;
extern void isysObjDeleteLock(void);
/* The wrapper tail-calls isysAddGroupWithLinkParam, so it passes that int
   result through. Declaring it void changes the registers used afterwards. */
extern int isysAddGroupWithLinkParamNoWait(void *, void *, int, int);

void iosDlLockObj(unsigned char *obj)
{
    isysObjDeleteLock();
    isysAddGroupWithLinkParamNoWait(obj, &B_00065018.grp[B_00065018.cur], 0, 0);
    B_00065018.lock[B_00065018.cur]++;
}
