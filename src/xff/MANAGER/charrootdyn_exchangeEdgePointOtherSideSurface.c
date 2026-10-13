extern void ExchangeGeometryPointerCollisionEdgeOtherSideInfo(void *, void *);
extern void *GetCharacterClass();
extern void motrootdyn_setupedgepoint(void *);

void charrootdyn_exchangeEdgePointOtherSideSurface(void)
{
    int var_v1;
    void *temp_a0;
    void *temp_v0;

    temp_v0 = GetCharacterClass();
    var_v1 = 0;
    temp_a0 = temp_v0 + 0xC0;
    if ((*(int *)((char *)(temp_v0) + 0x124)) != 0) {
        var_v1 = (*(int *)((char *)(temp_v0) + 0xF0)) == 4;
    }
    if (var_v1 == 0) {
        return;
    }
    ExchangeGeometryPointerCollisionEdgeOtherSideInfo(temp_a0, temp_a0);
    motrootdyn_setupedgepoint(temp_v0);
}
