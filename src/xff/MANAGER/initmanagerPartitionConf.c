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
    int i;
    D_00130344 = conf;
    p->ptn = &rootPtn;
    p++;
    for (i = 1; i < conf->num; i++, p++)
        p->ptn = iosCreatePartition(&rootPtn, p->size);
}
