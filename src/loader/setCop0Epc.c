void setCop0Epc(unsigned int epc) {
    __asm__ volatile("mtc0 %0, $14" : : "r"(epc));
}
