extern void GAMEUTIL_get_local_directionZ(void *, void *);

void SCRGetLocalDirZ(void *output, void *actor)
{
    GAMEUTIL_get_local_directionZ(output, actor);
}
