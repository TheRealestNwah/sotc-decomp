extern void DeleteTwoWayLink(void *);

void charrootdyn_resetkeepcolhitstatus(void *arg0) {
    if ((*(int *)((char *)(arg0) + 0xFF0)) != 0) {
        (*(int *)((char *)(arg0) + 0xFF0)) = 0;
        DeleteTwoWayLink(arg0 + 0x1010);
    }
    (*(int *)((char *)(arg0) + 0xFF4)) = 0;
}
