/* Staff-roll page drawer: returns 1 (clearing D_0017A84C) without the staff-roll font, otherwise uploads the texture, opens a GS layer and walks the staff-roll entries from the scroll position, replacing '_' with ' ' and the "copyright"/"camma" tokens from D_0017A858 with their characters, drawing text lines (types 0-5) that fall inside the window at B_00188630, advancing by line height, spacer or screen-height entries and reading layout parameters (types 10, 11, 13, 14, 18). Returns whether the last line is still above the bottom of the screen. The def's count and entries loads go through int indexing and the token shift loop has an empty asm barrier after p++ so gcc keeps the Original order. */
extern void *DldSysUndefSymbol;
extern char SH_StaffRollDefDEFAULT[];
extern char SH_TexListDeftex_staffroll_font_256[];
extern char rootPtn[];
extern int D_0017A820;
extern int D_0017A824;
extern int D_0017A828;
extern int D_0017A82C;
extern int D_0017A830;
extern int D_0017A840;
extern int D_0017A844;
extern int D_0017A84C;
extern int B_00188620[];
extern int B_00188630[];
extern int B_00188640[];
extern char RO_0017CD38[];
extern char RO_0017CD40[];
extern char RO_0017CD48[];
extern char RO_0017CD58[];
extern void *iosMallocAlign(int, int, int);
extern void iosFree(void *);
extern int iosSPrintf(char *, const char *, ...);
extern int sscanf(const char *, const char *, ...);
extern unsigned int strlen(const char *);
extern char *strstr(const char *, const char *);
extern int getDrawScreenHeight(void);
extern void texGetSize(void *, int *, int *);
extern void texTransRequest(void *, int, int);
extern void iosDlPushLayer(int);
extern void iosDlPopLayer(void);
extern void gsRegBegin(void);
extern void gsReg(long, long);
extern void gsRegEnd(void);
extern void func_00025330(int y, unsigned char *str, int mode); /* static in func_00025330.c */

typedef struct {
    int type;
    char *name;
} StaffEntry;

typedef struct {
    char pad[0xC];
    int count;
    StaffEntry *entries;
} StaffDef;

typedef struct {
    char *name;
    unsigned char c;
} Subst;

extern Subst D_0017A858[];

static int func_00025670(void *tex)
{
    StaffDef *def = (StaffDef *)((void *)DldSysUndefSymbol == (void *)SH_StaffRollDefDEFAULT ? 0 : SH_StaffRollDefDEFAULT);
    char *font = (void *)DldSysUndefSymbol == (void *)SH_TexListDeftex_staffroll_font_256 ? 0 : SH_TexListDeftex_staffroll_font_256;
    int shift = D_0017A828;
    int top = (D_0017A820 >> shift) << shift;
    int v;
    StaffEntry *e;
    int i;
    int count;
    unsigned char *buf;
    int line;
    int y;

    e = (StaffEntry *)((int *)def)[4];
    count = ((int *)def)[3];
    v = 0;

    if (font == 0) {
        D_0017A84C = 0;
        return 1;
    }
    buf = (unsigned char *)iosMallocAlign((int)rootPtn, 0x400, 0x10);
    texGetSize(tex, &D_0017A82C, &D_0017A830);
    y = top;
    line = y >> 4;
    D_0017A82C >>= 4;
    D_0017A830 >>= 4;
    iosDlPushLayer(0x1C);
    texTransRequest(tex, 0, 0);
    gsRegBegin();
    gsReg(0x14, 0x60);
    gsReg(0x47, 0x31001);
    gsReg(0x42, (0x80L << 32) | 0x44);
    gsReg(0, 0x156);
    gsRegEnd();
    for (i = 0; i < count; i++, e++) {
        unsigned int j;
        iosSPrintf((char *)buf, RO_0017CD38, e->name);
        for (j = 0; j < strlen((char *)buf); j++) {
            if (buf[j] == '_')
                buf[j] = ' ';
        }
        switch (e->type) {
        case 10:
            sscanf((char *)buf, RO_0017CD40, &B_00188620[0], &B_00188620[1]);
            break;
        case 11:
            sscanf((char *)buf, RO_0017CD48, &B_00188630[0], &B_00188630[1], &B_00188630[2], &B_00188630[3]);
            break;
        case 13:
            sscanf((char *)buf, RO_0017CD58, &D_0017A824);
            break;
        case 14:
            sscanf((char *)buf, RO_0017CD48, &B_00188640[0], &B_00188640[1], &B_00188640[2], &B_00188640[3]);
            break;
        case 7:
            sscanf((char *)buf, RO_0017CD58, &v);
            line += v;
            y += v << 4;
            break;
        case 8:
            sscanf((char *)buf, RO_0017CD58, &v);
            y += (getDrawScreenHeight() << 4) * v;
            line += getDrawScreenHeight() * v;
            break;
        case 9:
            sscanf((char *)buf, RO_0017CD58, &v);
            y += (getDrawScreenHeight() << 3) * v;
            line += (getDrawScreenHeight() >> 1) * v;
            break;
        case 6:
            sscanf((char *)buf, RO_0017CD58, &v);
            line += D_0017A824 * v;
            y += (D_0017A824 * v) << 4;
            break;
        case 18:
            sscanf((char *)buf, RO_0017CD40, &D_0017A840, &D_0017A844);
            break;
        case 12:
            break;
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5: {
            int mid = line + (D_0017A824 >> 1);
            if (B_00188630[0] < mid && mid < B_00188630[3]) {
                unsigned int k;
                for (k = 0; k < 2; k++) {
                    unsigned char *p;
                    while ((p = (unsigned char *)strstr((char *)buf, D_0017A858[k].name)) != 0) {
                        *p = D_0017A858[k].c;
                        do {
                            p++;
                            __asm__("");
                            *p = p[strlen(D_0017A858[k].name) - 1];
                        } while (*p != 0);
                    }
                }
                func_00025330(y, buf, e->type);
            }
            switch (e->type) {
            case 1:
            case 3:
            case 5:
                line += D_0017A824;
                y += D_0017A824 << 4;
                break;
            }
            break;
        }
        }
    }
    gsRegBegin();
    gsReg(8, 0);
    gsReg(0x47, 0x5100D);
    gsReg(0x42, (0x80L << 32) | 0x44);
    gsRegEnd();
    iosDlPopLayer();
    iosFree(buf);
    return line < getDrawScreenHeight() - D_0017A824;
}
