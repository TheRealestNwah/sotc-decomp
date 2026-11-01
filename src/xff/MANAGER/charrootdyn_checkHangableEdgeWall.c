extern unsigned long *GetCollisionDBAttributeAdr(void *db);
int charrootdyn_checkHangableEdgeWall(void *db)
{
    unsigned long attr = *GetCollisionDBAttributeAdr(db);
    unsigned long type = attr & 0x7C000000;
    unsigned long edge = attr & 0x003F800000000000;
    int r = 0;
    if (type != 0x18000000) {
        r = 1;
        if (edge == 0x0027800000000000) r = 0;
    }
    return r;
}
