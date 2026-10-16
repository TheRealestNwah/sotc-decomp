extern void charrootdyn_resetHColFindFlag(void *);
extern void charrootdyn_resetVColFindFlag(void *);
extern void charrootdyn_resetVColEdgeFindFlag(void *);
extern void charrootdyn_resetChainFindStatus(void *);
extern void charrootdyn_resetkeepcolhitstatus(void *);
extern void ReleaseCollisionFinder(void *);
extern void ReleaseCollisionEdgeLinkDB(void *);
extern void FlushLayoutObj(void *);
extern void FlushJudgeVolumeObj(void *);

void FlushCharacterObj(void *obj)
{
    char *o = obj;
    char *cls;

    switch ((unsigned char)o[8]) {
    case 9:
        cls = o + 0x90;
        break;
    case 0x16:
        cls = o + 0x90;
        break;
    default:
        cls = 0;
    }
    charrootdyn_resetHColFindFlag(cls);
    charrootdyn_resetVColFindFlag(cls);
    charrootdyn_resetVColEdgeFindFlag(cls);
    charrootdyn_resetChainFindStatus(cls);
    charrootdyn_resetkeepcolhitstatus(cls);
    ReleaseCollisionFinder(cls + 0xE20);
    ReleaseCollisionEdgeLinkDB(cls + 0xE40);
    FlushLayoutObj(o);
    FlushJudgeVolumeObj(o);
}
