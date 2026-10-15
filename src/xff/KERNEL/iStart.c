extern void (*D_00040BB4)(void);

void iStart(void)
{
    if (D_00040BB4 != 0) {
        D_00040BB4();
    }
}
