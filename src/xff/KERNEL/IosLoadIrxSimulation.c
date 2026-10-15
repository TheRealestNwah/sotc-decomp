extern unsigned char RO_00042A50[], RO_00042A70[], RO_00042A78[], RO_00042A90[], RO_00042AA0[], RO_00042AC0[];
extern int iosLoadIopModule(void *, void *, int, int);

int IosLoadIrxSimulation(void)
{
    iosLoadIopModule(RO_00042A50, RO_00042A70, 0, 0);
    iosLoadIopModule(RO_00042A78, RO_00042A90, 0, 0);
    return iosLoadIopModule(RO_00042AA0, RO_00042AC0, 0, 0);
}
