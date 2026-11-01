typedef struct {
    char pad0[0x18];
} WindSegment;

typedef struct {
    int type;
    WindSegment *segment;
} WindEmitter;

typedef struct {
    char pad0[0xC];
    int count;
    WindSegment *segments;
} WindSegmentSet;

extern WindEmitter *B_00149AB0[];
extern void func_000CB9E0(WindEmitter *);
extern void func_000CBA30(WindEmitter *);
extern void func_000CBA80(WindEmitter *);
extern void iosFree(void *);

void free_wind_segment(WindSegmentSet *set)
{
    int i;
    int j;
    int count;
    WindSegment *segs;

    if (set == 0)
        return;
    count = set->count;
    segs = set->segments;
    for (i = 0; i < count; i++) {
        for (j = 0; j < 80; j++) {
            WindEmitter *e = B_00149AB0[j];
            if (e != 0 && e->segment == &segs[i]) {
                if (e->type == 0)
                    func_000CB9E0(e);
                else if (e->type == 1)
                    func_000CBA30(e);
                else
                    func_000CBA80(e);
                iosFree(B_00149AB0[j]);
                B_00149AB0[j] = 0;
            }
        }
    }
}
