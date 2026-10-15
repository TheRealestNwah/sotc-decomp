extern int D_00040C30[];

int isysGetObjIdentifierByObj(unsigned char *obj)
{
    int t = obj[8];

    return t < 0x25 ? D_00040C30[t] : D_00040C30[0];
}
