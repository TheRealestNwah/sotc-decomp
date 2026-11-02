/*
 * gsframe: runs a PCSX2 GS dump through the Render translator and the
 * reference backend, and writes the displayed frame as a PNG.
 *
 *   gsframe <dump.gs> [-o frame.png] [--frame N] [--screenshot shot.png]
 *
 * --frame picks which vsync to stop at (1, the first, by default).
 * --screenshot also writes the PCSX2 screenshot stored in the dump, to
 * compare against. Compressed dumps must be decompressed first (zstd -d).
 * Format and capture steps: docs/render-translator.md.
 */
#include "gs_ref.h"
#include "gs_translate.h"
#include "gsdump.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static uint8_t *read_file(const char *path, size_t *size)
{
    FILE *f = fopen(path, "rb");
    if (!f)
        return NULL;
    uint8_t *data = NULL;
    if (fseek(f, 0, SEEK_END) == 0) {
        long n = ftell(f);
        if (n >= 0 && fseek(f, 0, SEEK_SET) == 0) {
            data = malloc(n ? (size_t)n : 1);
            if (data && fread(data, 1, (size_t)n, f) != (size_t)n) {
                free(data);
                data = NULL;
            }
            *size = (size_t)n;
        }
    }
    fclose(f);
    return data;
}

/* ---- a minimal PNG writer: stored (uncompressed) deflate blocks ---- */

static uint32_t crc_table[256];

static uint32_t crc32_update(uint32_t crc, const uint8_t *p, size_t n)
{
    if (!crc_table[1])
        for (uint32_t i = 0; i < 256; i++) {
            uint32_t c = i;
            for (int k = 0; k < 8; k++)
                c = c & 1 ? 0xEDB88320u ^ (c >> 1) : c >> 1;
            crc_table[i] = c;
        }
    crc = ~crc;
    while (n--)
        crc = crc_table[(crc ^ *p++) & 0xFF] ^ (crc >> 8);
    return ~crc;
}

static void put32(uint8_t *p, uint32_t v)
{
    p[0] = (uint8_t)(v >> 24);
    p[1] = (uint8_t)(v >> 16);
    p[2] = (uint8_t)(v >> 8);
    p[3] = (uint8_t)v;
}

static void chunk(FILE *f, const char *type, const uint8_t *data, size_t size)
{
    uint8_t head[8];
    put32(head, (uint32_t)size);
    memcpy(head + 4, type, 4);
    fwrite(head, 1, 8, f);
    fwrite(data, 1, size, f);
    uint32_t crc = crc32_update(crc32_update(0, (const uint8_t *)type, 4), data, size);
    put32(head, crc);
    fwrite(head, 1, 4, f);
}

static int write_png(const char *path, const uint8_t *rgba, int width, int height)
{
    size_t row = (size_t)width * 4 + 1, raw_size = row * (size_t)height;
    size_t blocks = (raw_size + 65534) / 65535;
    size_t z_size = 2 + raw_size + blocks * 5 + 4;
    uint8_t *z = malloc(z_size);
    uint8_t *raw = malloc(raw_size);
    if (!z || !raw) {
        free(z);
        free(raw);
        return -1;
    }
    for (int y = 0; y < height; y++) {
        raw[row * (size_t)y] = 0; /* filter: none */
        memcpy(raw + row * (size_t)y + 1, rgba + (size_t)y * width * 4, (size_t)width * 4);
    }
    size_t o = 0;
    z[o++] = 0x78;
    z[o++] = 0x01;
    uint32_t a = 1, b = 0;
    for (size_t i = 0; i < raw_size; i++) {
        a = (a + raw[i]) % 65521;
        b = (b + a) % 65521;
    }
    for (size_t pos = 0; pos < raw_size || pos == 0;) {
        size_t n = raw_size - pos > 65535 ? 65535 : raw_size - pos;
        z[o++] = pos + n == raw_size ? 1 : 0;
        z[o++] = (uint8_t)n;
        z[o++] = (uint8_t)(n >> 8);
        z[o++] = (uint8_t)~n;
        z[o++] = (uint8_t)(~n >> 8);
        memcpy(z + o, raw + pos, n);
        o += n;
        pos += n;
        if (n == 0)
            break;
    }
    put32(z + o, b << 16 | a);
    o += 4;

    FILE *f = fopen(path, "wb");
    if (!f) {
        free(z);
        free(raw);
        return -1;
    }
    static const uint8_t signature[8] = { 0x89, 'P', 'N', 'G', '\r', '\n', 0x1A, '\n' };
    uint8_t ihdr[13];
    put32(ihdr, (uint32_t)width);
    put32(ihdr + 4, (uint32_t)height);
    ihdr[8] = 8;  /* bit depth */
    ihdr[9] = 6;  /* RGBA */
    ihdr[10] = 0; /* deflate */
    ihdr[11] = 0; /* adaptive filtering */
    ihdr[12] = 0; /* no interlace */
    fwrite(signature, 1, 8, f);
    chunk(f, "IHDR", ihdr, sizeof(ihdr));
    chunk(f, "IDAT", z, o);
    chunk(f, "IEND", NULL, 0);
    int ok = ferror(f) == 0;
    ok &= fclose(f) == 0;
    free(z);
    free(raw);
    return ok ? 0 : -1;
}

static void usage(const char *argv0)
{
    fprintf(stderr, "usage: %s <dump.gs> [-o frame.png] [--frame N] [--screenshot shot.png]\n", argv0);
}

int main(int argc, char **argv)
{
    const char *input = NULL, *output = "frame.png", *shot = NULL;
    long stop_frame = 1;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0 && i + 1 < argc)
            output = argv[++i];
        else if (strcmp(argv[i], "--frame") == 0 && i + 1 < argc)
            stop_frame = strtol(argv[++i], NULL, 10);
        else if (strcmp(argv[i], "--screenshot") == 0 && i + 1 < argc)
            shot = argv[++i];
        else if (!input && argv[i][0] != '-')
            input = argv[i];
        else {
            usage(argv[0]);
            return 2;
        }
    }
    if (!input || stop_frame < 1) {
        usage(argv[0]);
        return 2;
    }

    size_t size = 0;
    uint8_t *data = read_file(input, &size);
    if (!data) {
        fprintf(stderr, "%s: cannot read\n", input);
        return 1;
    }
    const char *compression = gs_dump_compression(data, size);
    if (compression) {
        fprintf(stderr, "%s: %s-compressed; decompress it first (or set GSDumpCompression to Uncompressed)\n",
            input, compression);
        free(data);
        return 1;
    }
    struct gs_dump dump;
    const char *error = NULL;
    if (gs_dump_open(&dump, data, size, &error) != 0) {
        fprintf(stderr, "%s: %s\n", input, error);
        free(data);
        return 1;
    }
    printf("%s: serial %.*s, crc %08X, state version %u, %zu bytes of packets\n", input, (int)dump.serial_size,
        dump.serial, dump.crc, dump.state_version, dump.packets_size);

    struct gs_freeze freeze;
    if (gs_freeze_parse(dump.state, dump.state_size, &freeze) != 0) {
        fprintf(stderr, "%s: state freeze too small\n", input);
        free(data);
        return 1;
    }

    struct gs_translator t;
    struct gs_ref ref;
    if (gs_translator_init(&t, NULL) != 0) {
        fprintf(stderr, "out of memory\n");
        free(data);
        return 1;
    }
    gs_ref_init(&ref, t.vram);
    t.sink = gs_ref_sink(&ref);
    gs_translator_load(&t, &freeze, dump.privregs);

    size_t cursor = 0;
    struct gs_dump_packet packet;
    long frames = 0;
    int r;
    while ((r = gs_dump_next(&dump, &cursor, &packet)) == 1)
        if (gs_translator_packet(&t, &packet) && ++frames >= stop_frame)
            break;
    if (r < 0)
        fprintf(stderr, "%s: bad packet at offset %zu; stopping there\n", input, cursor);
    if (frames < stop_frame) {
        /* Dumps end without a final vsync: show what was drawn so far. */
        gs_translator_vsync(&t, 0);
        frames++;
        printf("dump ended after %ld vsync(s); showing the state at its end\n", frames - 1);
    }

    const struct gs_stats *s = &t.stats;
    printf("GIF: %llu tags, %llu/%llu/%llu qwords on paths 1/2/3\n", (unsigned long long)s->gif_tags,
        (unsigned long long)s->qwords[1], (unsigned long long)s->qwords[2], (unsigned long long)s->qwords[3]);
    printf("primitives: point %llu, line %llu, line strip %llu, triangle %llu, strip %llu, fan %llu, sprite %llu\n",
        (unsigned long long)s->primitives[0], (unsigned long long)s->primitives[1],
        (unsigned long long)s->primitives[2], (unsigned long long)s->primitives[3],
        (unsigned long long)s->primitives[4], (unsigned long long)s->primitives[5],
        (unsigned long long)s->primitives[6]);
    printf("batches: %llu (%llu vertices); transfers: %llu host, %llu local, %llu readback (%llu bytes)\n",
        (unsigned long long)s->batches, (unsigned long long)s->batch_vertices, (unsigned long long)s->transfers_host,
        (unsigned long long)s->transfers_local, (unsigned long long)s->transfers_readback,
        (unsigned long long)s->transfer_bytes);
    printf("approximated: %llu blends, %llu partial frame masks, %llu without colour clamp; %llu unknown regs\n",
        (unsigned long long)s->blend_approx, (unsigned long long)s->fbmsk_partial,
        (unsigned long long)s->colclamp_off, (unsigned long long)s->unknown_regs);
    printf("reference: %llu pixels, %llu render-target textures (%llu overlaps), %llu mipmapped prims, "
           "%llu bad textures, %llu unsupported targets\n",
        (unsigned long long)ref.stats.pixels, (unsigned long long)ref.stats.rt_textures,
        (unsigned long long)ref.stats.rt_overlaps, (unsigned long long)ref.stats.mip_ignored,
        (unsigned long long)ref.stats.bad_textures, (unsigned long long)ref.stats.unsupported_targets);

    int status = 0;
    if (ref.frame && write_png(output, ref.frame, ref.frame_width, ref.frame_height) == 0)
        printf("wrote %s (%dx%d, frame %ld)\n", output, ref.frame_width, ref.frame_height, frames);
    else {
        fprintf(stderr, "%s: cannot write\n", output);
        status = 1;
    }
    if (shot) {
        if (dump.screenshot
            && write_png(shot, dump.screenshot, (int)dump.screenshot_width, (int)dump.screenshot_height) == 0)
            printf("wrote %s (%ux%u, PCSX2's screenshot)\n", shot, dump.screenshot_width, dump.screenshot_height);
        else {
            fprintf(stderr, "%s: no screenshot in the dump, or cannot write\n", shot);
            status = 1;
        }
    }

    gs_ref_free(&ref);
    gs_translator_free(&t);
    free(data);
    return status;
}
