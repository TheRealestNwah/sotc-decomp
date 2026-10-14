extern void iosInitThreadSystem(void);
extern void iosInitMessageSystem(void);
extern void iosCreateIdleThread(void);
extern void iosCreatePrintMgr(void);
extern void iosCreateIopMgr(void);
void iosInit(void)
{
    iosInitThreadSystem();
    iosInitMessageSystem();
    iosCreateIdleThread();
    iosCreatePrintMgr();
    iosCreateIopMgr();
}
