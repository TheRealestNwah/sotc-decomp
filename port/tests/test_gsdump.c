/* PCSX2 GS dump reader, on dumps built by hand (synthetic data only). */
#include "check.h"
#include "gs_regs.h"
#include "gs_vram.h"
#include "gsdump.h"

#include <stdlib.h>
#include <string.h>

#define HEAD 356u
#define TAIL 84u
#define STATE_SIZE (HEAD + GS_VRAM_SIZE + TAIL)

struct buf {
    uint8_t *data;
    size_t size;
};

static void put8(struct buf *b, uint8_t v)
{
    b->data[b->size++] = v;
}

static void put32(struct buf *b, uint32_t v)
{
    for (int i = 0; i < 4; i++)
        put8(b, (uint8_t)(v >> (8 * i)));
}

static void put64_at(uint8_t *p, uint64_t v)
{
    for (int i = 0; i < 8; i++)
        p[i] = (uint8_t)(v >> (8 * i));
}

static void put_bytes(struct buf *b, const void *p, size_t n)
{
    memcpy(b->data + b->size, p, n);
    b->size += n;
}

/* A state freeze with recognisable registers, VRAM markers and Q = 1.5. */
static void put_state(struct buf *b)
{
    uint8_t *s = b->data + b->size;
    memset(s, 0, STATE_SIZE);
    s[0] = 9;                               /* version */
    put64_at(s + 4, 0x16);                  /* PRIM */
    put64_at(s + 4 + 4 * 8, 0x80ull << 32); /* TEXA */
    put64_at(s + 124 + 10 * 8, 0x1111);     /* ctx[0].frame */
    put64_at(s + 124 + 96 + 10 * 8, 0x2222); /* ctx[1].frame, at byte 300 */
    put64_at(s + 124 + 192, 0xAABBCCDD);    /* RGBAQ */
    s[HEAD] = 0x5A;                         /* first VRAM byte */
    s[HEAD + GS_VRAM_SIZE - 1] = 0xA5;      /* last VRAM byte */
    float q = 1.5f;
    memcpy(s + STATE_SIZE - 4, &q, 4);
    b->size += STATE_SIZE;
}

static void put_privregs(struct buf *b)
{
    memset(b->data + b->size, 0, GS_PRIV_SIZE);
    b->data[b->size + GS_PRIV_PMODE] = 1;
    b->size += GS_PRIV_SIZE;
}

static void put_packets(struct buf *b)
{
    static const uint8_t gif[16] = { 1, 2, 3 };
    put8(b, GS_DUMP_TRANSFER);
    put8(b, GS_DUMP_PATH3);
    put32(b, sizeof(gif));
    put_bytes(b, gif, sizeof(gif));
    put8(b, GS_DUMP_VSYNC);
    put8(b, 1);
    put8(b, GS_DUMP_READFIFO);
    put32(b, 64);
    put8(b, GS_DUMP_REGISTERS);
    memset(b->data + b->size, 0x33, GS_PRIV_SIZE);
    b->size += GS_PRIV_SIZE;
}

int main(void)
{
    struct buf b = { malloc(STATE_SIZE + 3 * GS_PRIV_SIZE + 4096), 0 };
    if (!b.data)
        return 1;

    /* New-style header: serial and a 2x1 screenshot inside it. */
    static const char serial[] = "SCUS-97472";
    static const uint8_t shot[8] = { 1, 2, 3, 255, 4, 5, 6, 255 };
    uint32_t header_size = 36 + 10 + 8;
    put32(&b, 0xFFFFFFFFu);
    put32(&b, header_size);
    put32(&b, 9);          /* state version */
    put32(&b, STATE_SIZE); /* state size */
    put32(&b, 36);         /* serial offset */
    put32(&b, 10);
    put32(&b, 0x1234ABCDu); /* crc */
    put32(&b, 2);           /* screenshot w, h */
    put32(&b, 1);
    put32(&b, 46); /* screenshot offset, size */
    put32(&b, 8);
    put_bytes(&b, serial, 10);
    put_bytes(&b, shot, 8);
    put_state(&b);
    put_privregs(&b);
    put_packets(&b);
    size_t full = b.size;
    /* A truncated transfer at the end. */
    put8(&b, GS_DUMP_TRANSFER);
    put8(&b, GS_DUMP_PATH1);
    put32(&b, 100);
    put8(&b, 0);

    struct gs_dump dump;
    const char *error = NULL;
    CHECK_EQ(gs_dump_open(&dump, b.data, b.size, &error), 0);
    CHECK_EQ(dump.crc, 0x1234ABCDu);
    CHECK_EQ(dump.state_version, 9u);
    CHECK_EQ(dump.serial_size, (size_t)10);
    CHECK(memcmp(dump.serial, serial, 10) == 0);
    CHECK_EQ(dump.screenshot_width, 2u);
    CHECK_EQ(dump.screenshot_height, 1u);
    CHECK(dump.screenshot && dump.screenshot[4] == 4);
    CHECK_EQ(dump.state_size, (size_t)STATE_SIZE);
    CHECK_EQ(dump.privregs[GS_PRIV_PMODE], 1);

    struct gs_freeze f;
    CHECK_EQ(gs_freeze_parse(dump.state, dump.state_size, &f), 0);
    CHECK_EQ(f.version, 9u);
    CHECK_EQ(f.prim, 0x16u);
    CHECK_EQ(f.texa, 0x80ull << 32);
    CHECK_EQ(f.ctx[0].frame, 0x1111u);
    CHECK_EQ(f.ctx[1].frame, 0x2222u);
    CHECK_EQ(f.rgbaq, 0xAABBCCDDu);
    CHECK_EQ(f.vram[0], 0x5A);
    CHECK_EQ(f.vram[GS_VRAM_SIZE - 1], 0xA5);
    CHECK(f.q == 1.5f);
    CHECK_EQ(gs_freeze_parse(dump.state, STATE_SIZE - 1, &f), -1);

    size_t cursor = 0;
    struct gs_dump_packet p;
    CHECK_EQ(gs_dump_next(&dump, &cursor, &p), 1);
    CHECK_EQ(p.type, GS_DUMP_TRANSFER);
    CHECK_EQ(p.path, GS_DUMP_PATH3);
    CHECK_EQ(p.size, 16u);
    CHECK(p.data && p.data[2] == 3);
    CHECK_EQ(gs_dump_next(&dump, &cursor, &p), 1);
    CHECK_EQ(p.type, GS_DUMP_VSYNC);
    CHECK_EQ(p.field, 1);
    CHECK_EQ(gs_dump_next(&dump, &cursor, &p), 1);
    CHECK_EQ(p.type, GS_DUMP_READFIFO);
    CHECK_EQ(p.size, 64u);
    CHECK_EQ(gs_dump_next(&dump, &cursor, &p), 1);
    CHECK_EQ(p.type, GS_DUMP_REGISTERS);
    CHECK_EQ(p.data[0], 0x33);
    size_t before = cursor;
    CHECK_EQ(gs_dump_next(&dump, &cursor, &p), -1);
    CHECK_EQ(cursor, before);

    /* Without the truncated packet the stream simply ends. */
    CHECK_EQ(gs_dump_open(&dump, b.data, full, &error), 0);
    cursor = 0;
    int packets = 0, r;
    while ((r = gs_dump_next(&dump, &cursor, &p)) == 1)
        packets++;
    CHECK_EQ(r, 0);
    CHECK_EQ(packets, 4);

    /* Truncated inside the state, or a bad header size. */
    CHECK_EQ(gs_dump_open(&dump, b.data, 8 + header_size + 100, &error), -1);
    CHECK(error != NULL);
    uint8_t bad[16] = { 0xFF, 0xFF, 0xFF, 0xFF, 4 };
    CHECK_EQ(gs_dump_open(&dump, bad, sizeof(bad), &error), -1);
    CHECK_EQ(gs_dump_open(&dump, bad, 4, NULL), -1);

    /* Old-style header: CRC, state size, state. */
    b.size = 0;
    put32(&b, 0xCAFEF00Du);
    put32(&b, STATE_SIZE);
    put_state(&b);
    put_privregs(&b);
    put_packets(&b);
    CHECK_EQ(gs_dump_open(&dump, b.data, b.size, &error), 0);
    CHECK_EQ(dump.crc, 0xCAFEF00Du);
    CHECK_EQ(dump.state_version, 0u);
    CHECK(dump.screenshot == NULL);
    CHECK_EQ(gs_freeze_parse(dump.state, dump.state_size, &f), 0);
    CHECK_EQ(f.ctx[1].frame, 0x2222u);
    cursor = 0;
    CHECK_EQ(gs_dump_next(&dump, &cursor, &p), 1);
    CHECK_EQ(p.type, GS_DUMP_TRANSFER);

    /* Compressed dumps are recognised and refused. */
    static const uint8_t zst[8] = { 0x28, 0xB5, 0x2F, 0xFD, 0, 0, 0, 0 };
    static const uint8_t xz[8] = { 0xFD, '7', 'z', 'X', 'Z', 0, 0, 0 };
    CHECK(gs_dump_compression(zst, sizeof(zst)) && strcmp(gs_dump_compression(zst, sizeof(zst)), "zstd") == 0);
    CHECK(gs_dump_compression(xz, sizeof(xz)) && strcmp(gs_dump_compression(xz, sizeof(xz)), "xz") == 0);
    CHECK(gs_dump_compression(b.data, b.size) == NULL);
    CHECK_EQ(gs_dump_open(&dump, zst, sizeof(zst), &error), -1);

    free(b.data);
    return check_finish("test_gsdump");
}
