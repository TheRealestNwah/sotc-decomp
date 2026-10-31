typedef struct {
    int state;
    char pad04[0x94];
} Slot65580;

typedef struct {
    char pad00[0x8];
    int status[7];
    int cur;
    int result;
    char pad2C[0xF0];
    Slot65580 slots[10];
} Obj65580;

static int func_00065580(Obj65580 *o)
{
    int i;
    int found;
    int s;
    int r;

    found = 0;
    if (o->cur != -1) {
        s = o->status[o->cur];
        if (s == 0) {
            for (i = 0; i < 10; i++) {
                if (o->slots[i].state == 1) {
                    found = 1;
                    break;
                }
            }
            if (found) {
                r = o->result;
                if (r < 0) {
                    r = 0;
                }
            } else {
                r = -1;
            }
        } else if (s == 1) {
            r = -3;
        } else if (s == 3 || s == 5) {
            r = -2;
        } else {
            r = -4;
        }
    } else {
        r = -3;
    }
    return r;
}
