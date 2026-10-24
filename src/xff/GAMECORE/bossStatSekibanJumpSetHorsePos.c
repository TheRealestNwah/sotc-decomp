typedef struct {
    float x, y, z, w;
} __attribute__((aligned(8))) Vector;

extern char gcGlobalVar[];
extern void *SCRGetFirstObj(void *list);
extern void YattsukeGetSeamlessAreaCenter(float *center, int area);
extern void gameflowSetPos(void *o, float x, float y, float z, float rx, float ry, float rz);

void bossStatSekibanJumpSetHorsePos(char *boss)
{
    float center[4] __attribute__((aligned(16)));
    Vector pos __attribute__((aligned(16)));
    void *horse = SCRGetFirstObj(gcGlobalVar + 0x2B4);

    if (horse != 0) {
        pos = (Vector){ -*(float *)(boss + 0x64), *(float *)(boss + 0x68), -*(float *)(boss + 0x6C), 1.0f };
        YattsukeGetSeamlessAreaCenter(center, *(unsigned char *)(boss + 0x51));
        __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                             "lqc2 vf6, 0x0(%2)\n"
                             "vadd.xyz vf5, vf5, vf6\n"
                             "sqc2 vf5, 0x0(%0)\n"
                             : : "r"(&pos), "r"(center), "r"(&pos) : "memory");
        gameflowSetPos(horse, -pos.x, pos.y, -pos.z, 0.0f, *(float *)(boss + 0x70), 0.0f);
    }
}
