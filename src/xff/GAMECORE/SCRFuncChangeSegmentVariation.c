extern int stagemanager_getSegmentVariation(void *);
extern void stagemanager_changeSegmentVariation(int);

void SCRFuncChangeSegmentVariation(void *actor, int v)
{
    if (v != stagemanager_getSegmentVariation(actor))
        stagemanager_changeSegmentVariation(v);
}
