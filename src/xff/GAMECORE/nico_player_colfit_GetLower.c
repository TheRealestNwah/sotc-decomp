typedef int s128 __attribute__((mode(TI)));
typedef unsigned int u128 __attribute__((mode(TI)));
extern void nico_IK_getAddSubPosition(s128 *, int, s128 *);
extern s128 B_0018B7D0;
extern s128 B_0018B7E0;

void nico_player_colfit_GetLower(int arg0)
{
    nico_IK_getAddSubPosition(&B_0018B7D0, arg0, &B_0018B7D0);
    B_0018B7E0 = B_0018B7D0;
}
