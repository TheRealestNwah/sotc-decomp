void RequestCharacterMotionShiftFunc(void *character, void *func)
{
    char *obj = character;
    char *cls;
    int n;

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
    n = (signed char)cls[0x53D];
    if (n < 8) {
        cls[0x53D]++;
        ((void **)(cls + 0x550))[n] = func;
    }
}
