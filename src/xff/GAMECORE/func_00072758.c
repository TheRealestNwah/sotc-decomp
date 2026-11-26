typedef struct {
    int v[10];
} OptionBlock;

typedef struct {
    int unk0[7];
    OptionBlock block;
    int unk44[5];
} OptionSave;

extern OptionSave B_0018B6A8;
extern void (*D_0017ADA8[])(int);
extern char gcGlobalVar[];
extern void _optionWorkSet(int, int);
extern int _optionWorkChk(int);
extern void setZoomKey(int);
extern void setInterestKey(int);
extern void setBossInterestKey(int);

static void func_00072758(void)
{
    OptionSave *s = &B_0018B6A8;
    void (**f)(int) = D_0017ADA8;

    f[0](s->unk0[0]);
    f[1](s->unk0[1]);
    f[2](s->unk0[2]);
    f[3](s->unk0[3]);
    f[4](s->unk0[4]);
    f[5](s->unk0[5]);
    f[6](s->unk0[6]);
    *(OptionBlock *)(gcGlobalVar + 0x314) = s->block;
    _optionWorkSet(7, s->block.v[6]);
    _optionWorkSet(8, s->block.v[2]);
    _optionWorkSet(9, s->block.v[4]);
    _optionWorkSet(10, s->block.v[3]);
    _optionWorkSet(11, s->block.v[5]);
    _optionWorkSet(12, s->block.v[7]);
    _optionWorkSet(13, s->block.v[8]);
    _optionWorkSet(14, s->block.v[9]);
    _optionWorkSet(15, s->block.v[0]);
    _optionWorkSet(16, s->block.v[1]);
    setZoomKey(_optionWorkChk(13));
    setInterestKey(_optionWorkChk(14));
    setBossInterestKey(_optionWorkChk(12));
    f[7](s->unk44[0]);
    f[8](s->unk44[1]);
    f[9](s->unk44[2]);
    f[10](s->unk44[3]);
    f[11](s->unk44[4]);
}

extern int *D_0017ADE0[];
extern int D_0017AE18[16];
extern char *D_STR_0017AE58[];
extern int B_0018B700[16];
extern int SeList_cancel;
extern int MakeStrHashValue(char *);
extern int SpriteMenuGetLayerNoByHash(int, int);
extern void SpriteMenuSetDispFlag(int, int, int);
extern void SpriteMenuSetLayer(int, int);
extern void SpriteMenuSetSelectSubMenuId(int, int);
extern int SpriteMenuGetSelectMenuMode(int);
extern void SpriteMenuSetPartsDefValueByHashStr(int, char *, char *, int);
extern void sePlaySystemSound(int);

#define LAYER(m, s) SpriteMenuGetLayerNoByHash(m, MakeStrHashValue(s))

/* Button-config rows in display order, as pointers into the saved key options. */
typedef struct {
    int *p[10];
} Keys;
static const Keys RO_0017E070 = {{&B_0018B6A8.block.v[2], &B_0018B6A8.block.v[4], &B_0018B6A8.block.v[5],
                                 &B_0018B6A8.block.v[3], &B_0018B6A8.block.v[6], &B_0018B6A8.block.v[7],
                                 &B_0018B6A8.block.v[0], &B_0018B6A8.block.v[1], &B_0018B6A8.block.v[9],
                                 &B_0018B6A8.block.v[8]}};

/* Hides the option menu, closes it and reapplies the saved options. */
static inline void closeOption(int menu, int *work)
{
    SpriteMenuSetDispFlag(menu, LAYER(menu, "OPTION_TOP"), 0);
    SpriteMenuSetDispFlag(menu, LAYER(menu, "OPTION_BG"), 0);
    work[3] = 3;
    func_00072758();
}

/* Option menu callback: opens the screen-position or button-config page, or closes the menu on cancel. */
static void func_00072928(int menu, int *work, unsigned int flags, unsigned int sel)
{
    unsigned int i, j;

    if (flags & 1) {
        switch (sel) {
        case 0:
        case 8:
            SpriteMenuSetSelectSubMenuId(menu, *D_0017ADE0[sel]);
            break;
        case 1:
            SpriteMenuSetDispFlag(menu, LAYER(menu, "OPTION_TOP"), 0);
            SpriteMenuSetDispFlag(menu, LAYER(menu, "SCR_POS_CURSOR"), 1);
            SpriteMenuSetLayer(menu, LAYER(menu, "SCR_POS_CURSOR"));
            break;
        case 11: {
            char *bc = "BUTTON_CONFIG";
            SpriteMenuSetDispFlag(menu, LAYER(menu, "OPTION_TOP"), 0);
            for (i = 0; i < 16; i++) {
                for (j = 0; j < 16; j++) {
                    if (D_0017AE18[j] == i) {
                        B_0018B700[i] = j;
                        break;
                    }
                }
            }
            for (i = 0; i < 10; i++) {
                Keys keys = RO_0017E070;
                int *t = D_0017AE18;
                SpriteMenuSetPartsDefValueByHashStr(menu, bc, D_STR_0017AE58[i], t[*keys.p[i]]);
            }
            SpriteMenuSetDispFlag(menu, LAYER(menu, "BUTTON_CONFIG"), 1);
            SpriteMenuSetLayer(menu, LAYER(menu, "BUTTON_CONFIG"));
        }
            break;
        default:
            if (D_0017ADE0[sel])
                SpriteMenuSetSelectSubMenuId(menu, *D_0017ADE0[sel]);
            break;
        case 12:
            closeOption(menu, work);
            break;
        }
    } else if (flags & 2) {
        if (SpriteMenuGetSelectMenuMode(menu) != 1) {
            closeOption(menu, work);
        }
    } else if (flags & 0x200) {
        if (SpriteMenuGetSelectMenuMode(menu) != 1) {
            sePlaySystemSound(SeList_cancel);
            closeOption(menu, work);
            if (work[7])
                *(int *)work[7] = 1;
        }
    }
}
