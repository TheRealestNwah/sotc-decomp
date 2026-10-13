void windowFontColor(void *arg0, void *arg1)
{
    (*(long *)((char *)(arg0) + 0x1F0)) = (long) (*(long *)((char *)(arg1) + 0));
    (*(long *)((char *)(arg0) + 0x1F8)) = (long) (*(long *)((char *)(arg1) + 8));
    (*(long *)((char *)(arg0) + 0x200)) = (long) (*(long *)((char *)(arg1) + 0x10));
    (*(long *)((char *)(arg0) + 0x208)) = (long) (*(long *)((char *)(arg1) + 0x18));
}
