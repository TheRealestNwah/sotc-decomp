typedef int s128 __attribute__((mode(TI)));
extern char B_0018B7B0[], B_0018B7E0[], B_0018B7F0[];
extern int B_0018B804;
extern float B_0018B800;
static float func_00091CE0(void *, s128 *, char *, char *, char *, int);
extern char *GetLayoutClass(void *);
extern void GetGeometryPointerPosition(s128 *, void *);

void nico_player_pendulum_Shoulder(void *object)
{
    s128 sampled;
    s128 position;
    void *actor = *(void **)object;
    if (B_0018B804 != 0) {
        GetGeometryPointerPosition(&sampled, GetLayoutClass(actor) + 0xC0);
        position = sampled;
        B_0018B800 = func_00091CE0(object, &position, B_0018B7B0,
                                 B_0018B7F0, B_0018B7E0, 0);
    }
}
