float iosGetRandom(void)
{
    float r;
    __asm__ __volatile__("vrnext.x vf05x, R\n"
                         "vrnext.x vf05x, R\n"
                         "vrnext.x vf05x, R\n"
                         "vrnext.x vf05x, R\n"
                         "vrnext.x vf05x, R\n"
                         "vrnext.x vf05x, R\n"
                         "vrnext.x vf05x, R\n"
                         "vrinit R, vf05x\n"
                         "vrnext.x vf05x, R\n"
                         "vrnext.x vf05x, R\n"
                         "vrnext.x vf05x, R\n"
                         "vrnext.x vf05x, R\n"
                         "vrnext.x vf05x, R\n"
                         "vrnext.x vf05x, R\n"
                         "vrnext.x vf05x, R\n"
                         "vsubw.x vf05, vf05, vf00w\n"
                         "qmfc2 $7, vf05\n"
                         "mtc1 $7, %0\n"
                         : "=f"(r) : : "$7");
    return r;
}
