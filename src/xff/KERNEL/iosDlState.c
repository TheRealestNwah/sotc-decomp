extern unsigned char B_00065018[0x30];

#ifdef NONMATCHING
int iosDlGetWorkBufId(void)
{
    return *(int *)(B_00065018 + 0x18);
}
#endif

#ifdef NONMATCHING
int iosDlGetTransBufId(void)
{
    return *(int *)(B_00065018 + 0x18) == 0;
}
#endif

#ifdef NONMATCHING
int iosDlGetLayer(void)
{
    return *(int *)(B_00065018 + 0x1C);
}
#endif

#ifdef NONMATCHING
int iosDlGetLayerNum(void)
{
    return *(int *)(B_00065018 + 0x14);
}
#endif
