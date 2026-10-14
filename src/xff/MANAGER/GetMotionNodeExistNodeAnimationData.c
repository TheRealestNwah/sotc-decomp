extern void *GetCharacterClass(void *);

extern int GetCharacterClassMotionPhysicalNodeID(void *, int);

unsigned int GetMotionNodeExistNodeAnimationData(void *arg0, int arg1) {
    if ((arg1 > 0) && (arg1 & 0x10000)) {
        return (unsigned int) ~GetCharacterClassMotionPhysicalNodeID(GetCharacterClass(arg0), arg1 & 0xFFFEFFFF) >> 0x1F;
    }
    return 1U;
}
