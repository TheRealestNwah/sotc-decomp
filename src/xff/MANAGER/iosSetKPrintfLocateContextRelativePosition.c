void iosSetKPrintfLocateContextRelativePosition(void *arg0, float fparg0, float fparg1)
{
    (*(float *)((char *)(arg0) + 0)) = (float) ((*(float *)((char *)(arg0) + 0)) - fparg0);
    (*(float *)((char *)(arg0) + 8)) = (float) ((*(float *)((char *)(arg0) + 8)) - fparg0);
    (*(float *)((char *)(arg0) + 4)) = (float) ((*(float *)((char *)(arg0) + 4)) - fparg1);
    (*(float *)((char *)(arg0) + 0xC)) = (float) ((*(float *)((char *)(arg0) + 0xC)) - fparg1);
}
