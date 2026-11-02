extern unsigned int D_00139E04;

/* func_00101AC0 inlined; that function itself does not match from this body yet. */
static inline void alignHeap(unsigned int size, unsigned int align) {
    unsigned int top = D_00139E04;

    top = (top + align - 1) / align;
    top *= align;
    D_00139E04 = top + size;
}

void func_00101AF0(unsigned int size) {
    alignHeap(size, 0x100);
}
