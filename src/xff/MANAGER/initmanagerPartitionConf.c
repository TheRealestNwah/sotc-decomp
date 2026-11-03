#ifdef NONMATCHING
/* loop increments land in swapped delay slots (i++ vs p++); otherwise matches. */
typedef struct Ptn Ptn;

typedef struct {
    int id;
    int size;
    Ptn *ptn;
} PartitionConf;

typedef struct {
    char pad[0xC];
    int num;
    PartitionConf *parts;
} ManagerConf;

extern Ptn rootPtn;
extern ManagerConf *D_00130344;
extern Ptn *iosCreatePartition(Ptn *, int);

void initmanagerPartitionConf(ManagerConf *conf)
{
    PartitionConf *p = conf->parts;
    int i = 1;
    D_00130344 = conf;
    p->ptn = &rootPtn;
    goto test;
loop:
    p++;
    i++;
    p->ptn = iosCreatePartition(&rootPtn, p->size);
test:
    if (i < conf->num) goto loop;
}
#endif
