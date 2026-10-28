typedef struct ReadPacket { int id, unknown04, size; } ReadPacket;
extern int nicosysdRecvDataRead(int, int, int);

static void func_000DFA98(int reader, ReadPacket *packet)
{
    unsigned char buffer[packet->size];
    nicosysdRecvDataRead(reader, (int)buffer, packet->size);
}
