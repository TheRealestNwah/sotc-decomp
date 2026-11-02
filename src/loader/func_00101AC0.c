extern unsigned int D_00139E04;

unsigned int func_00101AC0(unsigned int size, unsigned int align) {
    unsigned int addr = (D_00139E04 + align - 1) / align * align;

    D_00139E04 = addr + size;
    return addr;
}
