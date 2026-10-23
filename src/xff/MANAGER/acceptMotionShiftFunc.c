void acceptMotionShiftFunc(void *character)
{
    char *obj = character;
    char *cls;
    int count;
    int n;
    void (**func)(void *);

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
    count = (signed char)cls[0x53D];
    if (count > 0) {
        n = count;
        func = (void (**)(void *))(cls + 0x550);
        do {
            if (*func != 0) {
                (*func)(obj);
                *func = 0;
            }
            n--;
            func++;
        } while (n != 0);
    }
    cls[0x53D] = 0;
}
