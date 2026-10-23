typedef int s128 __attribute__((mode(TI)));

typedef union {
    struct {
        s128 pos;
        int count;
        short id;
        short type;
        short state;
        short active;
        int param;
    } s;
    char alias;
} PassageWork;

typedef struct {
    char pad[0x100];
    PassageWork works[20];
} PassageManager;

int forceAddPassageWork(PassageManager *manager, int id, int param, s128 *pos, int type, int index)
{
    PassageWork *work = &manager->works[index];

    if (index < 20) {
        work->s.pos = *pos;
        work->s.active = 1;
        work->s.id = id;
        work->s.param = param;
        work->s.type = type;
        work->s.state = 0;
        work->s.count = 0;
        return 1;
    }
    return 0;
}
