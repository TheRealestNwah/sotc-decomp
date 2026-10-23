typedef struct {
    long q[3];
    short state;
    short active;
    int param;
} PassageWork;

/* The char member makes the work copies alias num, so num is reloaded on
   every iteration, as in the original. */
typedef union {
    struct {
        char pad[0x100];
        PassageWork works[20];
        int num;
    } s;
    char alias;
} PassageManager;

void deletePassageWork(PassageManager *m, unsigned int index)
{
    unsigned int i;

    if (m->s.num != 0) {
        for (i = index; i < m->s.num - 1; i++) {
            m->s.works[i] = m->s.works[i + 1];
            m->s.works[i].state = 0;
        }
        m->s.num = m->s.num - 1;
    }
}
