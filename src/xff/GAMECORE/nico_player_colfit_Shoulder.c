typedef int s128 __attribute__((mode(TI)));
extern char B_0018B7B0[], B_0018B7E0[], B_0018B7F0[];
extern int B_0018B804;
extern float B_0018B800;
static int T_00092958(s128 *, void *, char *);
static float func_00091CE0(void *, s128 *, char *, char *, char *, int);

void nico_player_colfit_Shoulder(void *o)
{
    s128 v;
    int r = T_00092958(&v, o, B_0018B7B0);
    B_0018B804 = r;
    if (r != 0)
        B_0018B800 = func_00091CE0(o, &v, B_0018B7B0, B_0018B7F0, B_0018B7E0, 0);
}
