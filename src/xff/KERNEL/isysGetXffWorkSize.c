typedef struct {
    char pad[0xC];
    unsigned char nreloc;
    char pad2[0x1C - 0xD];
    int nsym;
    int pad3;
    int nall;
} XffHeader;

int isysGetXffWorkSize(XffHeader *xff)
{
    int extra;
    int count;
    int size;

    if (xff->nreloc != 0) {
        extra = xff->nreloc + 1;
    } else {
        extra = 2;
    }
    count = xff->nall - xff->nsym - extra;
    size = count != 0 ? count * 16 + 0x33 : 0;
    if (xff->nsym != 0) {
        size += xff->nsym * 16 + 0x33;
    }
    return size;
}
