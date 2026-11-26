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
