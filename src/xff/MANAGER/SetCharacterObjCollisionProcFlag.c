extern void FlushCollisionFinder(void *);

void SetCharacterObjCollisionProcFlag(void *o, int flag)
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

    if (*(signed char *)(cls + 0x52F) != 0 && flag == 0)
        FlushCollisionFinder(cls + 0xE20);
    cls[0x52F] = flag;
}
