extern void end_nico_yaw_pitch_cntrl(void *cntrl);

typedef struct {
    int a;
    int b;
    int c;
    char cntrl[4];
} NicoSight;

void end_nico_sight_on(NicoSight *s)
{
    s->a = 0;
    s->b = 0;
    s->c = 0;
    end_nico_yaw_pitch_cntrl(s->cntrl);
}
