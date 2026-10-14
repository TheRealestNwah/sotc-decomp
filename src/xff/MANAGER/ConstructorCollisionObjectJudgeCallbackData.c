typedef struct { int a; int b[5]; } T;
void ConstructorCollisionObjectJudgeCallbackData(T *p)
{
    int i;
    p->a = 0;
    for (i = 4; i >= 0; i--)
        p->b[i] = 0;
}
