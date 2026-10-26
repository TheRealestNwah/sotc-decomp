typedef void (*McWaitFunction)(void);
extern McWaitFunction B_0014DBB4;

void mcReqSetWaitFunc(McWaitFunction wait)
{
    B_0014DBB4 = wait;
}
