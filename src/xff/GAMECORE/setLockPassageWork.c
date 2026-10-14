extern char *getPassageWork(void *, int);
int setLockPassageWork(char *work, int locked)
{
    if (*(int *)(work + 0x380) != 0) {
  *(short *)(getPassageWork(work, 0) + 0x18)=locked;
  return 1;
    }
    return 0;
}
