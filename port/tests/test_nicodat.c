#include "check.h"
#include "disc_image.h"
#include "nicodat.h"
#include "synthetic.h"

#include <stdlib.h>
#include <string.h>

static void put_record(Bytes *b, uint32_t sector, uint32_t size)
{
    bytes_put_u32(b, sector);
    bytes_put_u32(b, size);
}

static void put_names(Bytes *b, const char *const *names, size_t count)
{
    Bytes block = {0};
    for (size_t i = 0; i < count; i++)
        bytes_put(&block, names[i], strlen(names[i]) + 1);
    bytes_put_u32(b, (uint32_t)block.size);
    bytes_put(b, block.data, block.size);
    bytes_free(&block);
}

/* A synthetic header in the order func_000DFEB0 reads it. */
static void build_header(Bytes *b, int with_special)
{
    static const char *const types[] = {"stagetexseg_def", "chara"};
    static const char *const special[] = {"boot.cfg", "font"};

    put_record(b, 100, 0x1000); /* boot */
    put_record(b, 200, 0x2000); /* root */

    bytes_put_u32(b, 2);
    put_names(b, types, 2);
    /* stagetexseg_def: three index entries, one localized */
    bytes_put_u32(b, 3);
    bytes_put_u16(b, 1);
    bytes_put_u16(b, 0);
    bytes_put_u16(b, 0x8000 | 2);
    bytes_put_u32(b, 2); /* files */
    bytes_put_u32(b, 6); /* localized */
    put_record(b, 300, 10);
    put_record(b, 301, 11);
    for (uint32_t i = 0; i < 6; i++)
        put_record(b, 400 + i, 20 + i);
    /* chara: empty tables */
    bytes_put_u32(b, 0);
    bytes_put_u32(b, 0);
    bytes_put_u32(b, 0);

    /* one map, name stored with its NUL */
    bytes_put_u32(b, 1);
    bytes_put_u32(b, 6);
    bytes_put(b, "world", 6);
    bytes_put_u32(b, 2); /* data type 2 */
    bytes_put_u32(b, 1); /* data type 1 */
    bytes_put_u32(b, 3); /* data type 0 */
    put_record(b, 500, 1); /* data type 2, variant 0 */
    put_record(b, 501, 2);
    put_record(b, 510, 3); /* data type 2, variant 1 */
    put_record(b, 511, 4);
    put_record(b, 520, 5); /* data type 1, variant 0 */
    put_record(b, 530, 6); /* data type 1, variant 1 */
    put_record(b, 540, 7); /* data type 0, variant 0 */
    put_record(b, 541, 8);
    put_record(b, 542, 9);
    put_record(b, 550, 10); /* data type 0, variant 1 */
    put_record(b, 551, 11);
    put_record(b, 552, 12);
    bytes_put_u32(b, 2); /* tex segs: x, y, seg */
    bytes_put_u32(b, (uint32_t)-5);
    bytes_put_u32(b, 4);
    bytes_put_u32(b, 0x100);
    bytes_put_u32(b, (uint32_t)-4);
    bytes_put_u32(b, (uint32_t)-5);
    bytes_put_u32(b, 0x105);

    bytes_put_u32(b, 2); /* ADPCM */
    put_record(b, 600, 0x800);
    put_record(b, 610, 0x1800);
    bytes_put_u32(b, 3); /* direct files */
    put_record(b, 700, 1);
    put_record(b, 701, 2);
    put_record(b, 702, 3);

    if (!with_special) {
        bytes_put_u32(b, 0);
        return;
    }
    bytes_put_u32(b, 2);
    put_names(b, special, 2);
    /* boot.cfg: two entries, a segment key and a map key */
    bytes_put_u32(b, 2);
    bytes_put_u32(b, 32);
    bytes_put(b, "\0\0\0\0\x12\0\0\0", 8);
    put_record(b, 900, 0x30);
    bytes_put(b, "\2\1\0\3\0\0\x34\x12", 8);
    put_record(b, 901, 0x40);
    /* font: a count the data doesn't hold */
    bytes_put_u32(b, 9);
    bytes_put_u32(b, 0);
}

static void check_archive(const NicoArchive *a, int with_special)
{
    const NicoSegmentType *t;
    const NicoMap *m;
    NicoRecord r;

    CHECK_EQ(a->boot.sector, 100u);
    CHECK_EQ(a->boot.size, 0x1000u);
    CHECK_EQ(a->root.sector, 200u);

    CHECK_EQ(a->segment_type_count, 2u);
    t = nico_find_segment_type(a, "stagetexseg_def");
    CHECK(t != NULL);
    if (t) {
        CHECK_EQ(nico_segment_record(t, 0, 1, &r), NICO_OK);
        CHECK_EQ(r.sector, 301u);
        CHECK_EQ(nico_segment_record(t, 1, 1, &r), NICO_OK);
        CHECK_EQ(r.sector, 300u);
        /* localized[2 + language - 1] */
        for (uint32_t language = 1; language <= 4; language++) {
            CHECK_EQ(nico_segment_record(t, 2, language, &r), NICO_OK);
            CHECK_EQ(r.sector, 400u + 2 + language - 1);
            CHECK_EQ(r.size, 20u + 2 + language - 1);
        }
        CHECK_EQ(nico_segment_record(t, 2, 5, &r), NICO_ERR_RANGE);
        CHECK_EQ(nico_segment_record(t, 2, 0, &r), NICO_ERR_ARGUMENT);
        CHECK_EQ(nico_segment_record(t, 3, 1, &r), NICO_ERR_RANGE);
    }
    t = nico_find_segment_type(a, "chara");
    CHECK(t != NULL);
    if (t) {
        CHECK_EQ(t->index_count, 0u);
        CHECK_EQ(nico_segment_record(t, 0, 1, &r), NICO_ERR_RANGE);
    }
    CHECK(nico_find_segment_type(a, "missing") == NULL);

    CHECK_EQ(a->map_count, 1u);
    m = nico_find_map(a, "world");
    CHECK(m != NULL);
    if (m) {
        CHECK_EQ(m->data_type[2].count, 2u);
        CHECK_EQ(m->data_type[1].count, 1u);
        CHECK_EQ(m->data_type[0].count, 3u);
        CHECK_EQ(nico_map_record(m, 2, 0, 1, &r), NICO_OK);
        CHECK_EQ(r.sector, 501u);
        CHECK_EQ(nico_map_record(m, 2, 1, 0, &r), NICO_OK);
        CHECK_EQ(r.sector, 510u);
        CHECK_EQ(nico_map_record(m, 1, 0, 0, &r), NICO_OK);
        CHECK_EQ(r.sector, 520u);
        CHECK_EQ(nico_map_record(m, 1, 1, 0, &r), NICO_OK);
        CHECK_EQ(r.sector, 530u);
        CHECK_EQ(nico_map_record(m, 0, 0, 2, &r), NICO_OK);
        CHECK_EQ(r.sector, 542u);
        CHECK_EQ(nico_map_record(m, 0, 1, 2, &r), NICO_OK);
        CHECK_EQ(r.sector, 552u);
        CHECK_EQ(r.size, 12u);
        CHECK_EQ(nico_map_record(m, 1, 0, 1, &r), NICO_ERR_RANGE);
        CHECK_EQ(nico_map_record(m, 3, 0, 0, &r), NICO_ERR_ARGUMENT);
        CHECK_EQ(nico_map_record(m, 0, 2, 0, &r), NICO_ERR_ARGUMENT);
        CHECK_EQ(m->tex_seg_count, 2u);
        CHECK_EQ(m->tex_segs[0].x, -5);
        CHECK_EQ(m->tex_segs[0].y, 4);
        CHECK_EQ(m->tex_segs[1].y, -5);
        CHECK_EQ(m->tex_segs[1].seg, 0x105u);
    }
    CHECK(nico_find_map(a, "worl") == NULL);

    CHECK_EQ(a->adpcm_count, 2u);
    CHECK_EQ(a->adpcm[1].sector, 610u);
    CHECK_EQ(a->direct_count, 3u);
    CHECK_EQ(a->direct[2].sector, 702u);
    CHECK_EQ(a->direct[2].size, 3u);
    CHECK_EQ(nico_record_offset(&a->direct[2]), 702u * 2048u);

    if (with_special) {
        const NicoSpecialFile *f = nico_find_special(a, "boot.cfg");
        CHECK_EQ(a->special_count, 2u);
        CHECK(f != NULL);
        if (f) {
            NicoSpecialEntry e;
            CHECK_EQ(f->entry_count, 2u);
            CHECK_EQ(f->data_size, 32u);
            CHECK_EQ(nico_special_entry(f, 0, &e), NICO_OK);
            CHECK_EQ(e.key[0], NICO_SPECIAL_SEGMENT);
            CHECK_EQ(e.key[4], 0x12);
            CHECK_EQ(e.record.sector, 900u);
            CHECK_EQ(e.record.size, 0x30u);
            CHECK_EQ(nico_special_entry(f, 1, &e), NICO_OK);
            CHECK_EQ(e.key[0], NICO_SPECIAL_MAP);
            CHECK_EQ(e.key[6] | e.key[7] << 8, 0x1234);
            CHECK_EQ(e.record.sector, 901u);
            CHECK_EQ(nico_special_entry(f, 2, &e), NICO_ERR_RANGE);
        }
        f = nico_find_special(a, "font");
        CHECK(f != NULL);
        if (f) {
            NicoSpecialEntry e;
            CHECK_EQ(f->entry_count, 9u);
            CHECK_EQ(f->data_size, 0u);
            CHECK_EQ(nico_special_entry(f, 0, &e), NICO_ERR_RANGE);
        }
    } else {
        CHECK_EQ(a->special_count, 0u);
        CHECK(nico_find_special(a, "boot.cfg") == NULL);
    }
}

static void test_parse(void)
{
    for (int with_special = 0; with_special <= 1; with_special++) {
        Bytes b = {0};
        NicoArchive *a = NULL;
        build_header(&b, with_special);
        CHECK_EQ(nico_parse_memory(b.data, b.size, &a), NICO_OK);
        CHECK(a != NULL);
        if (a) {
            CHECK_EQ(a->header_size, (uint64_t)b.size);
            check_archive(a, with_special);
            nico_free(a);
        }
        /* Data after the header (the assets) is not read. */
        bytes_put_zeros(&b, 5000);
        CHECK_EQ(nico_parse_memory(b.data, b.size, &a), NICO_OK);
        if (a) {
            CHECK_EQ(a->header_size, (uint64_t)b.size - 5000);
            nico_free(a);
        }
        bytes_free(&b);
    }
}

/* Every truncation of the header fails cleanly (and, under the sanitizers,
 * without leaks or out-of-bounds reads). */
static void test_truncated(void)
{
    Bytes b = {0};
    build_header(&b, 1);
    for (size_t n = 0; n < b.size; n++) {
        NicoArchive *a = (NicoArchive *)&b; /* must be reset to NULL */
        NicoStatus status = nico_parse_memory(b.data, n, &a);
        CHECK(status == NICO_ERR_TRUNCATED || status == NICO_ERR_FORMAT);
        CHECK(a == NULL);
    }
    bytes_free(&b);
}

static void test_malformed(void)
{
    NicoArchive *a = NULL;

    /* A huge count fails without allocating for it. */
    {
        Bytes b = {0};
        put_record(&b, 0, 0);
        put_record(&b, 0, 0);
        bytes_put_u32(&b, 0xFFFFFFFFu);
        bytes_put_zeros(&b, 64);
        CHECK_EQ(nico_parse_memory(b.data, b.size, &a), NICO_ERR_TRUNCATED);
        bytes_free(&b);
    }
    /* Fewer names than segment types. */
    {
        Bytes b = {0};
        put_record(&b, 0, 0);
        put_record(&b, 0, 0);
        bytes_put_u32(&b, 2);
        bytes_put_u32(&b, 4);
        bytes_put(&b, "abc", 4);
        bytes_put_zeros(&b, 64);
        CHECK_EQ(nico_parse_memory(b.data, b.size, &a), NICO_ERR_FORMAT);
        bytes_free(&b);
    }
    /* A names block without a final NUL. */
    {
        Bytes b = {0};
        put_record(&b, 0, 0);
        put_record(&b, 0, 0);
        bytes_put_u32(&b, 1);
        bytes_put_u32(&b, 3);
        bytes_put(&b, "abc", 3);
        bytes_put_zeros(&b, 64);
        CHECK_EQ(nico_parse_memory(b.data, b.size, &a), NICO_ERR_FORMAT);
        bytes_free(&b);
    }
    /* An index entry past its file table resolves to an error, not a read. */
    {
        Bytes b = {0};
        static const char *const names[] = {"t"};
        put_record(&b, 0, 0);
        put_record(&b, 0, 0);
        bytes_put_u32(&b, 1);
        put_names(&b, names, 1);
        bytes_put_u32(&b, 2);
        bytes_put_u16(&b, 5);
        bytes_put_u16(&b, 0x8000 | 5);
        bytes_put_u32(&b, 1);
        bytes_put_u32(&b, 1);
        put_record(&b, 1, 1);
        put_record(&b, 2, 2);
        for (int i = 0; i < 5; i++)
            bytes_put_u32(&b, 0); /* no maps, ADPCM, direct or special */
        CHECK_EQ(nico_parse_memory(b.data, b.size, &a), NICO_OK);
        if (a) {
            NicoRecord r;
            CHECK_EQ(nico_segment_record(&a->segment_types[0], 0, 1, &r), NICO_ERR_RANGE);
            CHECK_EQ(nico_segment_record(&a->segment_types[0], 1, 1, &r), NICO_ERR_RANGE);
            nico_free(a);
        }
        bytes_free(&b);
    }
    CHECK_EQ(nico_parse(NULL, NULL, 0, &a), NICO_ERR_ARGUMENT);
}

static int failing_read(void *context, uint64_t offset, void *buffer, size_t size)
{
    (void)context;
    (void)offset;
    (void)buffer;
    (void)size;
    return -1;
}

static void test_read_error(void)
{
    NicoArchive *a = NULL;
    CHECK_EQ(nico_parse(failing_read, NULL, 4096, &a), NICO_ERR_READ);
    CHECK(a == NULL);
}

/* NICO.DAT inside a synthetic Disc image, with an asset after the header. */
static void test_disc(void)
{
    for (int raw = 0; raw <= 1; raw++) {
        Bytes b = {0};
        IsoEntry entries[2];
        size_t size, raw_size;
        unsigned char *image, *data;
        DiscImage *disc = NULL;
        NicoArchive *a = NULL;
        DiscFile file;

        build_header(&b, 1);
        /* An asset at sector 2 of the archive. */
        bytes_put_zeros(&b, 2 * 2048 - b.size);
        bytes_put(&b, "ASSET", 5);
        entries[0].dir = NULL;
        entries[0].name = "OTHER.BIN;1";
        entries[0].data = "other file";
        entries[0].size = (uint32_t)strlen(entries[0].data);
        entries[1].dir = NULL;
        entries[1].name = "NICO.DAT;1";
        entries[1].data = b.data;
        entries[1].size = (uint32_t)b.size;
        image = iso_build(entries, 2, &size);
        data = image;
        if (raw) {
            data = iso_to_raw(image, size, 2, &raw_size);
            size = raw_size;
        }

        CHECK_EQ(disc_open_memory(data, size, &disc), DISC_OK);
        CHECK_EQ(nico_open_disc(disc, &a, &file), NICO_OK);
        CHECK_EQ(file.size, (uint32_t)b.size);
        if (a) {
            NicoRecord asset = {2, 5};
            char text[5];
            check_archive(a, 1);
            CHECK_EQ(disc_read(disc, nico_disc_offset(&file, &asset), text, sizeof text), DISC_OK);
            CHECK(memcmp(text, "ASSET", 5) == 0);
            nico_free(a);
        }
        disc_close(disc);

        if (data != image)
            free(data);
        free(image);
        bytes_free(&b);
    }

    /* A disc without NICO.DAT. */
    {
        IsoEntry entry = {NULL, "OTHER.DAT;1", "x", 1};
        size_t size;
        unsigned char *image = iso_build(&entry, 1, &size);
        DiscImage *disc = NULL;
        NicoArchive *a = NULL;
        CHECK_EQ(disc_open_memory(image, size, &disc), DISC_OK);
        CHECK_EQ(nico_open_disc(disc, &a, NULL), NICO_ERR_NOT_FOUND);
        disc_close(disc);
        free(image);
    }
}

int main(void)
{
    test_parse();
    test_truncated();
    test_malformed();
    test_read_error();
    test_disc();
    return check_finish("test_nicodat");
}
