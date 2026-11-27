#ifdef NONMATCHING /* 6 diffs: pinning the pool pointer to $s0 gives the Original's malloc-call setup and append loop. Left: the scheduler interleaves the three timer resets differently (other store orders score 9 or more). */
typedef union GWork {
    struct {
        char pad0[0xA8];
        union GWork *next;
    } s;
} GWork;

typedef struct GWorkList {
    int num;
    GWork *head;
    GWork *tail;
} GWorkList;

typedef struct {
    float dt;
    float half;
    float accum;
    int ticks;
} ParticleTimer;

typedef struct {
    const char *name;
    int a;
    int b;
} TextureStore;

typedef struct {
    const char *name;
    int a;
    int b;
    int c;
} Segment;

extern void *malloc_from_root_partition(int, const char *);
extern void isysInitGroup(void *);
extern void func_000C5608(void);

extern char *D_001370CC;
extern GWorkList B_001499B0;
extern char B_001499C0[];
extern ParticleTimer B_001499C8;
extern ParticleTimer B_001499D8;
extern ParticleTimer B_001499E8;
extern const char g_sPtclNullName[];
extern TextureStore g_ainParticleTextureStore[40];
extern Segment g_ainParticleSegment[50];

static inline void particleGWorkAppend(GWorkList *list, GWork *work)
{
    if (work == 0) {
        return;
    }
    if (list->tail != 0) {
        list->tail->s.next = work;
    } else {
        list->head = work;
    }
    work->s.next = 0;
    list->tail = work;
    list->num++;
}

static inline void resetTimer(ParticleTimer *t)
{
    t->accum = t->dt = t->half = 0.0f;
    t->ticks = 0;
}

void init_particle_manager(void)
{
    int i;
    register char **pool asm("$16") = &D_001370CC;

    *pool = malloc_from_root_partition(0x22600, "\xA5\xD1\xA1\xBC\xA5\xC6\xA5\xA3\xA5\xAF\xA5\xEB\xA5\xEF\xA1\xBC\xA5\xAF");
    B_001499B0.num = 0;
    B_001499B0.head = 0;
    B_001499B0.tail = 0;
    for (i = 0; i < 800; i++) {
        particleGWorkAppend(&B_001499B0, (GWork *)(*pool + i * 0xB0));
    }
    isysInitGroup(B_001499C0);
    for (i = 0; i < 40; i++) {
        g_ainParticleTextureStore[i].name = g_sPtclNullName;
        g_ainParticleTextureStore[i].a = 0;
        g_ainParticleTextureStore[i].b = 0;
    }
    for (i = 0; i < 50; i++) {
        g_ainParticleSegment[i].name = g_sPtclNullName;
        g_ainParticleSegment[i].a = 0;
        g_ainParticleSegment[i].b = 0;
        g_ainParticleSegment[i].c = 0;
    }
    resetTimer(&B_001499C8);
    resetTimer(&B_001499D8);
    resetTimer(&B_001499E8);
    func_000C5608();
}
#endif
