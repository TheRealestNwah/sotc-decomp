extern void DeleteCollMan(void *);
extern void DeleteGlobalLight(void *);
extern void DeleteGameLight(void *);

void SubCallDeleteFuncNonISysObjTypeRes(void *o, int type)
{
    switch (type) {
    case 15:
    case 16:
        break;
    case 17:
        DeleteCollMan(o);
        break;
    case 24:
        DeleteGlobalLight(o);
        break;
    case 27:
    case 28:
    case 33:
    case 34:
    case 35:
        DeleteGameLight(o);
        o = 0;
        break;
    }
}
