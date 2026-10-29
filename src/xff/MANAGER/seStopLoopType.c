typedef struct {
    int pad[2];
    unsigned int pad0 : 12;
    unsigned int loop : 1;
} SeInfo;

typedef struct {
    char pad[8];
    unsigned long pad0 : 37;
    unsigned long playing : 1;
    char pad10[0x30];
    int state;
    SeInfo *info;
} Se;

extern void sndSepStopReq(char *);

void seStopLoopType(Se *se)
{
    if (se->info->loop == 1) {
        se->state = 0;
        sndSepStopReq((char *)se);
    } else {
        se->playing = 0;
        se->state = 0;
    }
}
