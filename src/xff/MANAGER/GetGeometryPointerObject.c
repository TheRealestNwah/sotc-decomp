void *GetGeometryPointerObject(char *g)
{
    switch (*(unsigned int *)(g + 0x30)) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 8:
    case 9:
    case 10:
        return *(void **)g;
    case 6:
    case 7:
        break;
    }
    return 0;
}
