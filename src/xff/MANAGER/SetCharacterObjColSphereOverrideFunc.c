void SetCharacterObjColSphereOverrideFunc(void *o, void *func, void *arg)
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
    *(void **)(cls + 0x584) = func;
    *(void **)(cls + 0x580) = arg;
}
