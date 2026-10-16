void SetCharacterObjParentPointXZFitGpChangeJudgeFunc(void *o, void *func, int flag)
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
    *(void **)(cls + 0xA8C) = func;
    *(char *)(cls + 0xA90) = flag;
}
