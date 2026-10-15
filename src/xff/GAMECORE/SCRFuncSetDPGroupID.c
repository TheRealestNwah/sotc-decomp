extern char *getSCRDataCtrlWork(void *);
extern int getDPGroupID(void *, int);
extern void setUserPathGroupID(char *, int, int);

void SCRFuncSetDPGroupID(void *a, int b, int c, int d, int e, int name)
{
    char *w = getSCRDataCtrlWork(a);
    int id = getDPGroupID(a, name);
    if (id != -1) {
        setUserPathGroupID(w, id, -1);
        w = 0;
    }
}
