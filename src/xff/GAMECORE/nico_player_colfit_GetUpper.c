extern void nico_IK_getAddSubPosition(void *, int, void *);
extern unsigned char B_0018B7F0[];
extern unsigned char ZeroPoint[];

void nico_player_colfit_GetUpper(int arg0)
{
    nico_IK_getAddSubPosition(B_0018B7F0, arg0, ZeroPoint);
}
