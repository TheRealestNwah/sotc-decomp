/* EE addresses are 32-bit; retain byte offsets and original access order. */
void add_element_expression_change(volatile int *list, int type, int time, int flag, float start, float end, float speed) {
    int count;
    void *base;
    void *element;

    count = *list;
    base = (void *)((count * 0x18) + (int)list);
    if (count < 5) {
        element = base + 4;
        (*(volatile int *)((char *)(element) + 0x14)) = flag;
        (*(volatile int *)((char *)(base) + 4)) = type;
        (*(volatile float *)((char *)(element) + 4)) = start;
        (*(volatile float *)((char *)(element) + 8)) = end;
        (*(volatile int *)((char *)(element) + 0xC)) = time;
        (*(volatile float *)((char *)(element) + 0x10)) = speed;
        *list += 1;
    }
}
