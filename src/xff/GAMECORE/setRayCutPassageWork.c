extern char *getPassageWork(void *, unsigned int);
int setRayCutPassageWork(char *work, unsigned int index, int cut)
{
    if (index < *(unsigned int *)(work + 0x380)) {
  *(short *)(getPassageWork(work, index) + 0x1A)=cut;
  return 1;
    }
    return 0;
}
