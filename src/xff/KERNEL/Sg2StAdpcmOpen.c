typedef struct {
    unsigned char mode;
    char padding[3];
    unsigned int value04;
    unsigned int value08;
    unsigned int value0C;
    unsigned int value10;
    unsigned int value14;
} OpenParameters;

extern int Sg2RemoteSend(int, int, int, int);

int Sg2StAdpcmOpen(OpenParameters *parameters)
{
    unsigned int first, second, third;
    first = (unsigned int)parameters->mode << 24;
    first |= parameters->value04 & 0xFF0000;
    first |= parameters->value14 & 0xFF00;
    first |= (parameters->value10 & 0xFF0000) >> 16;
    second = (parameters->value10 << 16) |
             ((parameters->value0C >> 8) & 0xFFFF);
    third = (parameters->value0C << 24) |
            (parameters->value08 & 0xFFFFFF);
    Sg2RemoteSend(0x18, first, second, third);
    return 0;
}
