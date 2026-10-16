extern void SetCharacterObjDemoCutFinishFlag(void *, int);

void ExecCharaGeometryPostprocess(void *o)
{
    char *obj = o;
    char *cls;

    switch ((unsigned char)obj[8]) {
    case 9:
        cls = obj + 0x90;
        break;
    case 0x16:
        cls = obj + 0x90;
        break;
    default:
        cls = 0;
    }

    if (*(char **)(cls + 0x19C) != 0)
        *(*(char **)(cls + 0x19C) + 0x8C) = 0;
    if (*(signed char *)(cls + 0x10A0) != 0) {
        SetCharacterObjDemoCutFinishFlag(o, 0);
        if (*(char **)(cls + 0x19C) != 0)
            *(*(char **)(cls + 0x19C) + 0x8C) = 1;
    }
}
