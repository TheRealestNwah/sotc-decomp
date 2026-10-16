extern char RO_001810A8[];
extern char RO_001810C8[];
extern char RO_001810E8[];
extern char RO_00181108[];
extern char RO_00181130[];
extern char RO_00181158[];
extern char RO_00181188[];
extern char RO_001811A8[];

char *get_camera_mode_name(int mode)
{
    if (mode == 0)
        return RO_001810A8;
    if (mode == 1)
        return RO_001810C8;
    if (mode == 2)
        return RO_001810E8;
    if (mode == 3)
        return RO_00181108;
    if (mode == 4)
        return RO_00181130;
    if (mode == 5)
        return RO_00181158;
    if (mode == 6)
        return RO_00181188;
    return RO_001811A8;
}
