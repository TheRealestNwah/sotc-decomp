typedef struct Ptn Ptn;
typedef union { unsigned short *p; unsigned short h[2]; } ShockPointer;
typedef struct { ShockPointer base, a, b, c; } ShockVoiceSet;
extern Ptn rootPtn;
extern void *iosMallocAlign(Ptn *, int, int);
extern char *sheetFileGetDataAdrs(void *);
extern void sheetFileRead(void *, void *, int);
extern void Init_ShockVoiceSet(ShockVoiceSet *, unsigned short *);
extern int Shock_SetShockVoiceSet(unsigned int, int);
int svdLoadFile(void *file, int unused, int size)
{
    unsigned short *buffer = iosMallocAlign(&rootPtn, size, 16);
    ShockVoiceSet *voice = iosMallocAlign(&rootPtn, sizeof(ShockVoiceSet), 16);
    unsigned int bank = *(unsigned int *)((char *)file + 8);
    char *metadata = sheetFileGetDataAdrs(file);
    sheetFileRead(file, buffer, size);
    Init_ShockVoiceSet(voice, buffer);
    Shock_SetShockVoiceSet(bank, (int)voice);
    *(ShockVoiceSet **)(metadata + 0xC) = voice;
    return 0;
}
