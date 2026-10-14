typedef int s128 __attribute__((mode(TI)));

typedef struct {
    s128 q;
} Vec4;

typedef struct {
    Vec4 pos;
    Vec4 dir;
    Vec4 target;
    int node;
    float time;
    float weight;
    int flag;
} PinAttackIK;

extern void *GetCharacterClass(void *);
extern Vec4 ZeroPoint;
extern Vec4 ZeroVector;

void initPinAttackIKWork(void *arg0, void *arg1, PinAttackIK *ik)
{
    int n = *(int *)(*(char **)((char *)GetCharacterClass(arg0) + 0x358) + 0x20);
    int i;

    for (i = 0; i < n; i++) {
        ik->pos = ZeroPoint;
        ik->dir = ZeroVector;
        ik->weight = -1.0f;
        ik->time = -1.0f;
        ik->node = -1;
        ik->flag = 0;
        ik->target = ZeroPoint;
        ik++;
    }
}
