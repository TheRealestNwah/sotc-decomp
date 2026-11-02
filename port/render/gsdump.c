#include "gsdump.h"

#include "gs_regs.h"
#include "gs_vram.h"

#include <string.h>

/* GSDumpHeader: nine u32 fields, packed to 4. */
#define DUMP_HEADER_SIZE 36u

/* What a v9 freeze holds after VRAM: four GIF paths (128-bit tag + u32 reg), then Q. */
#define FREEZE_TAIL_SIZE (4u * (16u + 4u) + 4u)

/* Registers at the start of a freeze: version, 15 environment registers, 2 contexts of 12, 5 vertex registers. */
#define FREEZE_HEAD_SIZE (4u + 15u * 8u + 2u * 12u * 8u + 5u * 8u)

static uint32_t rd32(const uint8_t *p)
{
    return (uint32_t)p[0] | (uint32_t)p[1] << 8 | (uint32_t)p[2] << 16 | (uint32_t)p[3] << 24;
}

static uint64_t rd64(const uint8_t *p)
{
    return (uint64_t)rd32(p) | (uint64_t)rd32(p + 4) << 32;
}

const char *gs_dump_compression(const uint8_t *data, size_t size)
{
    static const uint8_t zstd[4] = { 0x28, 0xB5, 0x2F, 0xFD };
    static const uint8_t xz[6] = { 0xFD, '7', 'z', 'X', 'Z', 0x00 };
    if (size >= 4 && memcmp(data, zstd, 4) == 0)
        return "zstd";
    if (size >= 6 && memcmp(data, xz, 6) == 0)
        return "xz";
    return NULL;
}

int gs_dump_open(struct gs_dump *dump, const uint8_t *data, size_t size, const char **error)
{
    const char *dummy;
    size_t pos;
    if (!error)
        error = &dummy;
    memset(dump, 0, sizeof(*dump));

    if (gs_dump_compression(data, size)) {
        *error = "dump is compressed; decompress it first (zstd -d / xz -d) or set PCSX2's GS dump compression to Uncompressed";
        return -1;
    }
    if (size < 8) {
        *error = "file too small for a GS dump";
        return -1;
    }

    if (rd32(data) == 0xFFFFFFFFu) {
        uint32_t header_size = rd32(data + 4);
        if (header_size < DUMP_HEADER_SIZE || header_size > size - 8) {
            *error = "bad dump header size";
            return -1;
        }
        const uint8_t *h = data + 8;
        dump->state_version = rd32(h);
        dump->state_size = rd32(h + 4);
        uint32_t serial_off = rd32(h + 8), serial_size = rd32(h + 12);
        dump->crc = rd32(h + 16);
        dump->screenshot_width = rd32(h + 20);
        dump->screenshot_height = rd32(h + 24);
        uint32_t shot_off = rd32(h + 28), shot_size = rd32(h + 32);
        if ((uint64_t)serial_off + serial_size > header_size || (uint64_t)shot_off + shot_size > header_size) {
            *error = "dump header fields point outside the header";
            return -1;
        }
        dump->serial = (const char *)h + serial_off;
        dump->serial_size = serial_size;
        if (shot_size && (uint64_t)dump->screenshot_width * dump->screenshot_height * 4 == shot_size)
            dump->screenshot = h + shot_off;
        else
            dump->screenshot_width = dump->screenshot_height = 0;
        pos = 8 + (size_t)header_size;
    } else {
        /* Old dumps: CRC, state size, state. */
        dump->crc = rd32(data);
        dump->state_size = rd32(data + 4);
        pos = 8;
    }

    if (dump->state_size > size - pos || GS_PRIV_SIZE > size - pos - dump->state_size) {
        *error = "dump truncated inside the GS state";
        return -1;
    }
    dump->state = data + pos;
    pos += dump->state_size;
    dump->privregs = data + pos;
    pos += GS_PRIV_SIZE;
    dump->packets = data + pos;
    dump->packets_size = size - pos;
    return 0;
}

int gs_dump_next(const struct gs_dump *dump, size_t *cursor, struct gs_dump_packet *packet)
{
    const uint8_t *p = dump->packets;
    size_t n = dump->packets_size, pos = *cursor;
    if (pos >= n)
        return 0;
    memset(packet, 0, sizeof(*packet));
    packet->type = p[pos++];
    switch (packet->type) {
    case GS_DUMP_TRANSFER:
        if (n - pos < 5)
            return -1;
        packet->path = p[pos];
        packet->size = rd32(p + pos + 1);
        pos += 5;
        if (packet->size > n - pos)
            return -1;
        packet->data = p + pos;
        pos += packet->size;
        break;
    case GS_DUMP_VSYNC:
        if (n - pos < 1)
            return -1;
        packet->field = p[pos++];
        break;
    case GS_DUMP_READFIFO:
        if (n - pos < 4)
            return -1;
        packet->size = rd32(p + pos);
        pos += 4;
        break;
    case GS_DUMP_REGISTERS:
        if (n - pos < GS_PRIV_SIZE)
            return -1;
        packet->data = p + pos;
        pos += GS_PRIV_SIZE;
        break;
    default:
        return -1;
    }
    *cursor = pos;
    return 1;
}

int gs_freeze_parse(const uint8_t *state, size_t size, struct gs_freeze *f)
{
    memset(f, 0, sizeof(*f));
    if (size < FREEZE_HEAD_SIZE + GS_VRAM_SIZE + FREEZE_TAIL_SIZE)
        return -1;

    const uint8_t *p = state;
    f->version = rd32(p);
    p += 4;
    uint64_t *env[] = { &f->prim, &f->prmodecont, &f->texclut, &f->scanmsk, &f->texa, &f->fogcol, &f->dimx, &f->dthe,
        &f->colclamp, &f->pabe, &f->bitbltbuf, &f->trxdir, &f->trxpos, &f->trxreg };
    for (size_t i = 0; i < sizeof(env) / sizeof(env[0]); i++, p += 8)
        *env[i] = rd64(p);
    p += 8; /* second, obsolete TRXREG */
    for (int c = 0; c < 2; c++) {
        struct gs_freeze_context *x = &f->ctx[c];
        uint64_t *regs[] = { &x->xyoffset, &x->tex0, &x->tex1, &x->clamp, &x->miptbp1, &x->miptbp2, &x->scissor,
            &x->alpha, &x->test, &x->fba, &x->frame, &x->zbuf };
        for (size_t i = 0; i < sizeof(regs) / sizeof(regs[0]); i++, p += 8)
            *regs[i] = rd64(p);
    }
    uint64_t *vtx[] = { &f->rgbaq, &f->st, &f->uv, &f->fog, &f->xyz };
    for (size_t i = 0; i < sizeof(vtx) / sizeof(vtx[0]); i++, p += 8)
        *vtx[i] = rd64(p);

    f->vram = state + size - FREEZE_TAIL_SIZE - GS_VRAM_SIZE;
    uint32_t q = rd32(state + size - 4);
    memcpy(&f->q, &q, sizeof(f->q));
    return 0;
}
