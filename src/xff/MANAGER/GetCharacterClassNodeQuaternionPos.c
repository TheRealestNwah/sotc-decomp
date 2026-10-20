extern void GetMotionMatrix(int, int, int, int, char *, char *);
void GetCharacterClassNodeQuaternionPos(int *quat, int *pos, char *cls, int node, int direct)
{
    if (direct) {
        *quat = *(int *)(cls + 0x154) + node * 16;
        *pos = *(int *)(cls + 0x158) + node * 64 + 0x30;
    } else {
        if (*(signed char *)(cls + 0x533) == 0) {
            GetMotionMatrix(*(int *)(cls + 0x344), *(int *)(cls + 0x348), *(int *)(cls + 0x358), *(int *)(cls + 0x340), cls + 0x40, cls + 0x90);
            *(signed char *)(cls + 0x533) = 1;
        }
        *quat = *(int *)(cls + 0x348) + node * 16;
        *pos = *(int *)(cls + 0x344) + node * 64 + 0x30;
    }
}