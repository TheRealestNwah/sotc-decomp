typedef struct Link { struct Link *next; struct Link *prev; } Link;
extern int DeleteTwoWayLink(Link *);

void charrootdyn_resetkeepcolhitstatus(void *arg0) {
    if ((*(int *)((char *)(arg0) + 0xFF0)) != 0) {
        (*(int *)((char *)(arg0) + 0xFF0)) = 0;
        DeleteTwoWayLink((Link *)(arg0 + 0x1010));
    }
    (*(int *)((char *)(arg0) + 0xFF4)) = 0;
}
