extern char *GetSubLinkClass(unsigned char *object);

int KickParticleGetResourceId(unsigned char *object)
{
    return **(int **)(GetSubLinkClass(object) + 0x10);
}
