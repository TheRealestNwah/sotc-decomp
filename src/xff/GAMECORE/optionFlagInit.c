extern void *memset(void *, int, unsigned int);

extern char B_00183E68[];

extern void optionMenuParamSetDefault(void);

void optionFlagInit(void)
{
    memset(B_00183E68, 0, 0x88);
    optionMenuParamSetDefault();
}
