int CheckLegalCollisionGP(char *gp)
{
    int type = *(int *)(gp + 0x30);
    switch (type) { case 2: case 3: case 4: case 5: return 1; } return 0;
}
