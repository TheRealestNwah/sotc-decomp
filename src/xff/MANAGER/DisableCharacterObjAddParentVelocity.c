void DisableCharacterObjAddParentVelocity(void *o)
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
    *(char *)(cls + 0xA28) = 1;
}
