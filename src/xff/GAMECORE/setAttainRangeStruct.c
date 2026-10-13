void setAttainRangeStruct(void *arg0, void *arg1)
{
    (*(long *)((char *)(arg0) + 0x3E0)) = (long) (*(long *)((char *)(arg1) + 0));
    (*(long *)((char *)(arg0) + 0x3E8)) = (long) (*(long *)((char *)(arg1) + 8));
    (*(long *)((char *)(arg0) + 0x3F0)) = (long) (*(long *)((char *)(arg1) + 0x10));
    (*(long *)((char *)(arg0) + 0x3F8)) = (long) (*(long *)((char *)(arg1) + 0x18));
}
