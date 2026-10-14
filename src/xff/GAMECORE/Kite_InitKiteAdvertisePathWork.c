extern void Kite_InitKitePathWork();

void Kite_InitKiteAdvertisePathWork(void *arg0)
{
    Kite_InitKitePathWork();
    (*(int *)((char *)(arg0) + 4)) = 0;
}
