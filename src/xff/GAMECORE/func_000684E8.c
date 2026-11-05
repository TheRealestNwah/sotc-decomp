extern char RO_0017DB80[];
extern char RO_0017DBA8[];
extern char RO_0017DBC0[];
extern char RO_0017DBD8[];
extern char RO_0017DC00[];
extern char RO_0017DCC8[];
extern char RO_0017DDA0[];
extern char RO_0017DDE0[];
extern char RO_0017DDF0[];

extern void SpriteMenuSetPartsDefValueByHashStrWithoutErrorCheck(void *, char *, char *, int);

static void func_000684E8(void *menu, int value)
{
    SpriteMenuSetPartsDefValueByHashStrWithoutErrorCheck(menu, RO_0017DDE0, RO_0017DDF0, value);
    SpriteMenuSetPartsDefValueByHashStrWithoutErrorCheck(menu, RO_0017DBA8, RO_0017DDF0, value);
    SpriteMenuSetPartsDefValueByHashStrWithoutErrorCheck(menu, RO_0017DB80, RO_0017DDF0, value);
    SpriteMenuSetPartsDefValueByHashStrWithoutErrorCheck(menu, RO_0017DBD8, RO_0017DDF0, value);
    SpriteMenuSetPartsDefValueByHashStrWithoutErrorCheck(menu, RO_0017DBC0, RO_0017DDF0, value);
    SpriteMenuSetPartsDefValueByHashStrWithoutErrorCheck(menu, RO_0017DC00, RO_0017DDF0, value);
    SpriteMenuSetPartsDefValueByHashStrWithoutErrorCheck(menu, RO_0017DCC8, RO_0017DDF0, value);
    SpriteMenuSetPartsDefValueByHashStrWithoutErrorCheck(menu, RO_0017DDA0, RO_0017DDF0, value);
}
