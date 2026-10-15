extern char *func_0000AF78(int);
extern void iosJumpRecoverPoint(void *, ...);
extern unsigned char RO_00042DE8[];
extern unsigned char RO_00042E90[];

void DldExceptionByOriginAdr(int adr)
{
    char *name = func_0000AF78(adr);
    if (name != 0)
        iosJumpRecoverPoint(RO_00042DE8, name, adr);
    else
        iosJumpRecoverPoint(RO_00042E90, adr);
}
