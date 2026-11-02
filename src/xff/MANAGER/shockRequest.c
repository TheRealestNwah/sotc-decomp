typedef struct ShockPattern {
    short data[2];
} ShockPattern;

typedef struct ShockParam {
    char pad0[4];
    short port;
} ShockParam;

extern int **D_001396A0;
extern int D_001396A4;
extern char iosDefaultPadData[];
extern int Shock_Request(void *pad, int port, ShockPattern pattern, int id, int flag);

int shockRequest(ShockParam *param)
{
    ShockPattern pattern = {{0, 0x40FF}};
    void *pad = iosDefaultPadData + 0x58;
    int port = param->port;
    int result = 0;

    if (D_001396A0 != 0) {
        if (*D_001396A0 != 0)
            result = Shock_Request(pad, port, pattern, D_001396A4++, 0);
    }
    return result;
}
