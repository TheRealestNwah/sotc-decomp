

extern void FlushModifiedManager(void *);

int FlushCollisionWorkByWorkStruct(void *arg0, int arg1, int arg2, int arg3) {
    int var_s1;
    void *var_s0;

    var_s0 = (*(void **)((char *)(arg0) + 0x24));
    if (arg1 > 0) {
        var_s1 = arg1;
        do {
            var_s1 -= 1;
            FlushModifiedManager(var_s0);
            FlushModifiedManager(var_s0 + 0x30);
            FlushModifiedManager(var_s0 + 0x48);
            FlushModifiedManager(var_s0 + 0x18);
            var_s0 += 0x60;
        } while (var_s1 != 0);
    }
    if (arg3 != 0) {
        FlushModifiedManager(arg0 + 0x28);
        FlushModifiedManager(arg0 + 0x40);
    }
    if (arg2 != 0) {
        FlushModifiedManager(arg0 + 0x58);
        FlushModifiedManager(arg0 + 0x70);
    }
    (*(int *)((char *)(arg0) + 0x1C)) = 0;
    return 1;
}
