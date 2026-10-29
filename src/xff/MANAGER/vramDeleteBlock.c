extern void iosFree(int);

void vramDeleteBlock(int block)
{
    iosFree(block);
}
