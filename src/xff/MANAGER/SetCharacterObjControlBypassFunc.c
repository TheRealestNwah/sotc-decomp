void SetCharacterObjControlBypassFunc(void *character, int value)
{
    char *obj = character;
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
    *(int *)(cls + 0x9CC) = value;
}
