extern int B_0018B808[];

typedef union {
    long l;
    int i[2];
} SlipVal;

typedef struct {
    int flag;
    SlipVal val;
} SlipWork;

void player_initSlipEffect(void *p, SlipWork *w)
{
    w->flag = 0;
    w->val.l = 0;
    B_0018B808[0] = 0;
    B_0018B808[1] = 0;
    B_0018B808[2] = 0;
    B_0018B808[3] = 0;
    B_0018B808[8] = 0;
    B_0018B808[4] = 0;
    B_0018B808[5] = 0;
    B_0018B808[6] = 0;
    B_0018B808[9] = 0;
    B_0018B808[10] = 0;
    B_0018B808[11] = 0;
    B_0018B808[12] = 0;
    B_0018B808[7] = 1;
    B_0018B808[13] = 2;
    B_0018B808[14] = 0;
}
