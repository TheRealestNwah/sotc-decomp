typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; int i[4]; } U128;

typedef struct {
    char pad0[0x30];
    U128 pos;
} TailBone;

typedef struct {
    int chara;
    int unk4;
    int unk8;
    int unkC;
    int unk10;
    int unk14;
    char pad18[0xB4 - 0x18];
    int unkB4;
    int unkB8;
} TailCtrl;

typedef struct {
    U128 rot[0x14];
    U128 vel[0x14];
    U128 pos[0x14];
    char pad3C0[0x4];
    int unk3C4;
    float unk3C8;
} TailWork;

typedef struct {
    char pad0[0x68];
    unsigned int unk68;
} TailFlags;

typedef struct {
    char pad0[0x1C0];
    TailFlags *unk1C0;
    char pad1C4[0x1118 - 0x1C4];
    TailWork *tail;
} CharacterClass;

typedef struct {
    char pad0[0x190];
    float unk190;
} GlobalVar;

extern GlobalVar gcGlobalVar;
extern int D_0017B8C4;
extern CharacterClass *GetCharacterClass(int);
extern void GetMotionMatrixOfTargetFromRoot(int, int, int, int, int, int, int);

void nico_calcTailGenealogicalNodeHead(TailCtrl *a)
{
    int chara = a->chara;
    TailWork *t = GetCharacterClass(chara)->tail;
    TailFlags **f = &GetCharacterClass(chara)->unk1C0;
    int *p = &D_0017B8C4;

    *p = 0;
    t->pos[0].q = ((TailBone *)a->unk8)[a->unk14].pos.q;
    ((U128 *)(*p * 16 + (int)t))->q = ((U128 *)a->unkC)[a->unk14].q;
    t->vel[*p].q = ((U128 *)a->unk4)[a->unk14].q;
    GetMotionMatrixOfTargetFromRoot(a->unk8, a->unkC, a->unk10, a->unk4, a->unkB4, a->unkB8, a->unk14);
    if (((*f)->unk68 >> 3) & 1) {
        t->unk3C4 = 1;
        t->unk3C8 = 1.0f;
    } else {
        if (0.0f < t->unk3C8) {
            t->unk3C8 = t->unk3C8 - gcGlobalVar.unk190 / 3.0f;
            t->unk3C8 = (0.0f <= t->unk3C8) ? t->unk3C8 : 0.0f;
        }
        t->unk3C4 = 0;
    }
    D_0017B8C4++;
}
