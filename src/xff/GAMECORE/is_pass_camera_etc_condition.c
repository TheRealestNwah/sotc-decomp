extern int opflowAdvertiseDemoStat;
extern int GAMEUTIL_is_boss_booting(void);

typedef struct {
    int a;
    int b;
    int c;
    int d;
    int e;
} CameraEtcFlags;

int is_pass_camera_etc_condition(unsigned int cond, CameraEtcFlags *f)
{
    int r = 0;

    switch (cond) {
    case 0:
        r = 0;
        break;
    case 1:
        r = 1;
        break;
    case 2:
        r = f->a;
        break;
    case 3:
        r = f->b;
        break;
    case 4:
        r = GAMEUTIL_is_boss_booting();
        break;
    case 5:
        r = f->c;
        break;
    case 6:
        r = f->d;
        break;
    case 7:
        r = f->d == 0;
        break;
    case 8:
        if (opflowAdvertiseDemoStat == 1)
            r = 1;
        break;
    case 9:
        if (opflowAdvertiseDemoStat == 2)
            r = 1;
        break;
    case 10:
        r = f->e;
        break;
    case 11:
        r = f->e == 0;
        break;
    }
    return r;
}
