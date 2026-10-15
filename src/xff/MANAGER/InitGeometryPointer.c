extern unsigned char InitialGeometryPointer[];

void InitGeometryPointer(void *arg0)
{
    (*(long *)((char *)(arg0) + 0)) = (long) (*(long *)((char *)(InitialGeometryPointer) + 0));
    (*(long *)((char *)(arg0) + 8)) = (long) (*(long *)((char *)(InitialGeometryPointer) + 8));
    (*(long *)((char *)(arg0) + 0x10)) = (long) (*(long *)((char *)(InitialGeometryPointer) + 0x10));
    (*(long *)((char *)(arg0) + 0x18)) = (long) (*(long *)((char *)(InitialGeometryPointer) + 0x18));
    (*(long *)((char *)(arg0) + 0x20)) = (long) (*(long *)((char *)(InitialGeometryPointer) + 0x20));
    (*(long *)((char *)(arg0) + 0x28)) = (long) (*(long *)((char *)(InitialGeometryPointer) + 0x28));
    (*(long *)((char *)(arg0) + 0x30)) = (long) (*(long *)((char *)(InitialGeometryPointer) + 0x30));
    (*(long *)((char *)(arg0) + 0x38)) = (long) (*(long *)((char *)(InitialGeometryPointer) + 0x38));
}
