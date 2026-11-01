typedef int s128 __attribute__((mode(TI)));

extern s128 YUnitVector;
extern void ResetCharacterClassWaterStatus(char *);
extern void UnlinkSecureParentInfo(char *);
extern int DeleteTwoWayLink(char *);

void ResetCharacterClassDynamicsElement(char *p)
{
    *(char *)(p + 0x531) = 0;
    *(char *)(p + 0x10C0) = 0;
    *(char *)(p + 0x35D) = 0;
    *(char *)(p + 0x35C) = 0;
    *(char *)(p + 0x35E) = 0;
    *(char *)(p + 0x35F) = 0;
    *(int *)(p + 0xFC0) = 0;
    *(char *)(p + 0x530) = 0;
    *(char *)(p + 0x535) = 0;
    *(char *)(p + 0x10A4) = 0;
    *(char *)(p + 0x10A3) = 0;
    *(char *)(p + 0x10A1) = 0;
    *(char *)(p + 0x10A6) = 0;
    ResetCharacterClassWaterStatus(p);
    UnlinkSecureParentInfo(p + 0xF70);
    if (*(int *)(p + 0xF3C) != 0) {
        *(int *)(p + 0xF3C) = 0;
        DeleteTwoWayLink(p + 0xF30);
    }
    if (*(int *)(p + 0xE70) != 0) {
        *(int *)(p + 0xE70) = 0;
        DeleteTwoWayLink(p + 0xF60);
    }
    UnlinkSecureParentInfo(p + 0xDA0);
    *(int *)(p + 0xFD0) = 0;
    *(int *)(p + 0x610) = 0;
    *(int *)(p + 0x670) = 0;
    *(long *)(p + 0x690) = 0;
    *(int *)(p + 0x6B4) = 0;
    *(int *)(p + 0xEE8) = 0;
    *(int *)(p + 0x6B8) = 0;
    *(int *)(p + 0x6C0) = 0;
    *(s128 *)(p + 0x6A0) = YUnitVector;
    *(char *)(p + 0xA24) = 1;
    *(char *)(p + 0x10A7) = 0;
    *(char *)(p + 0xA95) = 0;
    *(char *)(p + 0xA94) = 0;
    if (*(int *)(p + 0xFF0) != 0) {
        *(int *)(p + 0xFF0) = 0;
        DeleteTwoWayLink(p + 0x1010);
    }
    *(int *)(p + 0xFF4) = 0;
}
