typedef struct Partition Partition;
typedef struct { int start; int end; } SoundDefinition;
typedef struct { int state; int definition; } SoundEntry;
typedef struct { char unknown[0xC]; int count; SoundDefinition *definitions; } SoundLayout;
extern SoundLayout SH_SpuLayoutDEFAULT;
extern Partition rootPtn;
extern SoundEntry *B_001502C0;
extern int B_001502C4;
extern char B_0014F8C0[];
extern void *iosMallocAlign(Partition *, int, int);
extern void *memset(void *, int, unsigned int);
extern void sndSepInitTickParam(char *, int, int);
void initSoundManager(void)
{
    int count = SH_SpuLayoutDEFAULT.count;
    int *definitions = (int *)SH_SpuLayoutDEFAULT.definitions;
    int size = count * sizeof(SoundEntry);
    int i;
    B_001502C0 = iosMallocAlign(&rootPtn, size, 4);
    memset(B_001502C0, 0, size);
    for (i = 0; i < count; ++i)
        ((int *)B_001502C0)[i * 2 + 1] = (int)&definitions[i * 2];
    B_001502C4 = count;
    sndSepInitTickParam(B_0014F8C0, 32, 80);
}
