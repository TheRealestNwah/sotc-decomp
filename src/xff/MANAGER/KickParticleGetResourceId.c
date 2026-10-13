extern void *GetSubLinkClass();

int KickParticleGetResourceId(void)
{
    return *(*(int **)((char *)(GetSubLinkClass()) + 0x10));
}
