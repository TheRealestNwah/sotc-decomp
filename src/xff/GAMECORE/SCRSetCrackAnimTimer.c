extern char *GetCharacterClass(int);
extern char *GetSCRCharaAIWorkPtr(int);
extern int SCRGetFirstObj(void *);
extern unsigned char gcGlobalVar[];

void SCRSetCrackAnimTimer(void)
{
    int boss = SCRGetFirstObj(gcGlobalVar + 0x2B8);
    char *work;

    if (boss == 0) {
        return;
    }
    work = GetSCRCharaAIWorkPtr(boss);
    if ((*(long *)(GetCharacterClass(boss) + 0x690) & 0x01E00000) == 0x200000) {
        *(float *)(work + 0x41CC) += 0.5f;
    } else {
        *(float *)(work + 0x41CC) = 0.0f;
    }
    if (*(float *)(work + 0x41CC) > 5.0f) {
        *(float *)(work + 0x41CC) = 5.0f;
    }
}
