typedef struct {
    char pad[0x18];
    char name[0x20];
} McDirEnt;

extern int mcGetInfo(int, int);
extern int mcReqGetDir(int, int, const char *, int, int, McDirEnt *, int *);
extern int strcmp(const char *, const char *);
extern void gstatBootMcSetExistIcoData(int);

static void func_00035470(int mask) {
    char *names[6] = {
        "BISCPS-11003ico", "BASCUS-97113ico", "BESCES-50760ico",
        "BISCPS-56001ico", "BISCPS-55001ico", "BISCCS-40005ico",
    };
    McDirEnt dir[5];
    int count;
    int found;
    int port;
    int off;
    int i;
    char *nm;
    unsigned int j;

    found = 0;
    for (port = 0; mask > 0; mask >>= 1, port++) {
        if (mcGetInfo(port, 0) != 0) {
            continue;
        }
        off = 0;
        if (mask & 1) {
            do {
                if (mcReqGetDir(port, 0, "/*ico", off, 5, dir, &count) != 0) {
                    goto next;
                }
                i = 0;
                if (i < count) {
                    nm = dir[0].name;
                    do {
                        for (j = 0; j < 6; j++) {
                            if (strcmp(names[j], nm) == 0) {
                                found = 1;
                                goto end;
                            }
                        }
                        nm += sizeof(McDirEnt);
                    } while (++i < count);
                }
                off += count;
            } while (count == 5);
        }
    next:;
    }
end:
    gstatBootMcSetExistIcoData(found);
}
