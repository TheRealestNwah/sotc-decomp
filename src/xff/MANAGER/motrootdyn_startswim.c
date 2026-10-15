extern void ForceUnparentLayoutObj(void *);

void motrootdyn_startswim(void *actor, char *m)
{
    ForceUnparentLayoutObj(actor);
    *(float *)(m + 0xB30) = *(float *)(m + 0x34) * 0.5f;
}
