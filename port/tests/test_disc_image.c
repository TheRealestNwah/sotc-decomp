#include "check.h"
#include "disc_image.h"
#include "synthetic.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned char nico[5000];
static unsigned char file_bin[3000];
static const char readme[] = "hello";

static unsigned char *build_sample(size_t *size)
{
    IsoEntry entries[] = {
        {NULL, "NICO.DAT;1", nico, sizeof nico},
        {NULL, "README.;1", readme, sizeof readme - 1},
        {"DATA", "FILE.BIN;1", file_bin, sizeof file_bin},
        {NULL, "EMPTY.TXT;1", NULL, 0},
    };
    for (size_t i = 0; i < sizeof nico; i++)
        nico[i] = (unsigned char)(i * 7 + 1);
    for (size_t i = 0; i < sizeof file_bin; i++)
        file_bin[i] = (unsigned char)(i ^ 0x5A);
    return iso_build(entries, sizeof entries / sizeof entries[0], size);
}

static void check_contents(DiscImage *disc)
{
    DiscFile file;
    unsigned char buffer[5000];

    CHECK_EQ(disc_find_file(disc, "\\NICO.DAT;1", &file), DISC_OK);
    CHECK_EQ(file.size, sizeof nico);
    CHECK_EQ(disc_read(disc, (uint64_t)file.lsn * DISC_SECTOR_SIZE, buffer, file.size), DISC_OK);
    CHECK(memcmp(buffer, nico, sizeof nico) == 0);
    /* A read that starts and ends inside sectors. */
    CHECK_EQ(disc_read(disc, (uint64_t)file.lsn * DISC_SECTOR_SIZE + 2000, buffer, 2100), DISC_OK);
    CHECK(memcmp(buffer, nico + 2000, 2100) == 0);

    CHECK_EQ(disc_find_file(disc, "\\DATA\\FILE.BIN;1", &file), DISC_OK);
    CHECK_EQ(file.size, sizeof file_bin);
    CHECK_EQ(disc_read(disc, (uint64_t)file.lsn * DISC_SECTOR_SIZE, buffer, file.size), DISC_OK);
    CHECK(memcmp(buffer, file_bin, sizeof file_bin) == 0);
}

static void test_find(void)
{
    size_t size;
    unsigned char *image = build_sample(&size);
    DiscImage *disc = NULL;
    DiscFile a, b;

    CHECK_EQ(disc_open_memory(image, size, &disc), DISC_OK);
    CHECK_EQ(disc_raw_sector_size(disc), 2048u);
    CHECK_EQ(disc_sector_count(disc), (uint32_t)(size / 2048));
    check_contents(disc);

    /* Spellings of the same path. */
    CHECK_EQ(disc_find_file(disc, "\\NICO.DAT;1", &a), DISC_OK);
    const char *spellings[] = {"NICO.DAT", "nico.dat", "/NICO.DAT", "\\\\nico.DAT;1", "NICO.DAT;1"};
    for (size_t i = 0; i < sizeof spellings / sizeof spellings[0]; i++) {
        CHECK_EQ(disc_find_file(disc, spellings[i], &b), DISC_OK);
        CHECK_EQ(a.lsn, b.lsn);
        CHECK_EQ(a.size, b.size);
    }
    CHECK_EQ(disc_find_file(disc, "data/file.bin", &b), DISC_OK);

    /* A name stored without an extension ends in '.' on the disc. */
    CHECK_EQ(disc_find_file(disc, "README", &b), DISC_OK);
    CHECK_EQ(b.size, 5u);
    CHECK_EQ(disc_find_file(disc, "EMPTY.TXT", &b), DISC_OK);
    CHECK_EQ(b.size, 0u);

    CHECK_EQ(disc_find_file(disc, "MISSING.DAT", &b), DISC_ERR_NOT_FOUND);
    CHECK_EQ(disc_find_file(disc, "NICO.DA", &b), DISC_ERR_NOT_FOUND);
    CHECK_EQ(disc_find_file(disc, "DATA", &b), DISC_ERR_NOT_FOUND);
    CHECK_EQ(disc_find_file(disc, "\\", &b), DISC_ERR_NOT_FOUND);
    CHECK_EQ(disc_find_file(disc, "NICO.DAT\\X", &b), DISC_ERR_NOT_FOUND);
    CHECK_EQ(disc_find_file(disc, "DATA\\MISSING", &b), DISC_ERR_NOT_FOUND);

    /* Reads past the end. */
    {
        unsigned char sector[2048];
        uint32_t count = disc_sector_count(disc);
        CHECK_EQ(disc_read_sectors(disc, count - 1, 1, sector), DISC_OK);
        CHECK_EQ(disc_read_sectors(disc, count, 1, sector), DISC_ERR_RANGE);
        CHECK_EQ(disc_read_sectors(disc, count - 1, 2, sector), DISC_ERR_RANGE);
        CHECK_EQ(disc_read(disc, (uint64_t)count * 2048 - 1, sector, 2), DISC_ERR_RANGE);
        CHECK_EQ(disc_read_sectors(disc, 0xFFFFFFFFu, 2, sector), DISC_ERR_RANGE);
    }

    disc_close(disc);
    free(image);
}

typedef struct Listing {
    int files;
    int directories;
    int saw_nico;
} Listing;

static int count_entry(void *context, const char *name, const DiscFile *file, int is_directory)
{
    Listing *l = context;
    (void)file;
    if (is_directory)
        l->directories++;
    else
        l->files++;
    if (strcmp(name, "NICO.DAT") == 0)
        l->saw_nico = 1;
    return 0;
}

static int stop_at_first(void *context, const char *name, const DiscFile *file, int is_directory)
{
    (void)name;
    (void)file;
    (void)is_directory;
    ++*(int *)context;
    return 1;
}

static void test_list(void)
{
    size_t size;
    unsigned char *image = build_sample(&size);
    DiscImage *disc = NULL;
    Listing l = {0, 0, 0};
    int calls = 0;

    CHECK_EQ(disc_open_memory(image, size, &disc), DISC_OK);
    CHECK_EQ(disc_list_directory(disc, "\\", count_entry, &l), DISC_OK);
    CHECK_EQ(l.files, 3);
    CHECK_EQ(l.directories, 1);
    CHECK(l.saw_nico);
    memset(&l, 0, sizeof l);
    CHECK_EQ(disc_list_directory(disc, "DATA", count_entry, &l), DISC_OK);
    CHECK_EQ(l.files, 1);
    CHECK_EQ(l.directories, 0);
    CHECK_EQ(disc_list_directory(disc, "", stop_at_first, &calls), DISC_OK);
    CHECK_EQ(calls, 1);
    CHECK_EQ(disc_list_directory(disc, "NICO.DAT", count_entry, &l), DISC_ERR_NOT_FOUND);
    disc_close(disc);
    free(image);
}

/* A root directory spanning several sectors, so records must not be read
 * across sector boundaries. */
static void test_large_directory(void)
{
    enum { COUNT = 150 };
    static char names[COUNT][32];
    static unsigned char data[COUNT];
    IsoEntry entries[COUNT];
    size_t size;
    unsigned char *image;
    DiscImage *disc = NULL;

    for (int i = 0; i < COUNT; i++) {
        snprintf(names[i], sizeof names[i], "FILE_WITH_LONG_NAME_%03d.BIN;1", i);
        data[i] = (unsigned char)i;
        entries[i].dir = NULL;
        entries[i].name = names[i];
        entries[i].data = &data[i];
        entries[i].size = 1;
    }
    image = iso_build(entries, COUNT, &size);
    CHECK_EQ(disc_open_memory(image, size, &disc), DISC_OK);
    for (int i = 0; i < COUNT; i += 7) {
        char want[32];
        DiscFile file;
        unsigned char byte = 0xFF;
        snprintf(want, sizeof want, "file_with_long_name_%03d.bin", i);
        CHECK_EQ(disc_find_file(disc, want, &file), DISC_OK);
        CHECK_EQ(disc_read(disc, (uint64_t)file.lsn * 2048, &byte, 1), DISC_OK);
        CHECK_EQ(byte, (unsigned char)i);
    }
    {
        DiscFile file;
        CHECK_EQ(disc_find_file(disc, "FILE_WITH_LONG_NAME_149.BIN", &file), DISC_OK);
    }
    disc_close(disc);
    free(image);
}

static void test_raw_sectors(void)
{
    for (int mode = 1; mode <= 2; mode++) {
        size_t size, raw_size;
        unsigned char *image = build_sample(&size);
        unsigned char *raw = iso_to_raw(image, size, mode, &raw_size);
        DiscImage *disc = NULL;
        CHECK_EQ(disc_open_memory(raw, raw_size, &disc), DISC_OK);
        CHECK_EQ(disc_raw_sector_size(disc), 2352u);
        CHECK_EQ(disc_sector_count(disc), (uint32_t)(size / 2048));
        check_contents(disc);
        disc_close(disc);
        free(raw);
        free(image);
    }
}

static void test_malformed(void)
{
    size_t size;
    unsigned char *image = build_sample(&size);
    unsigned char *copy = malloc(size);
    DiscImage *disc = NULL;
    DiscFile file;
    static unsigned char zeros[64 * 1024];

    CHECK_EQ(disc_open_memory(zeros, sizeof zeros, &disc), DISC_ERR_FORMAT);
    CHECK(disc == NULL);
    CHECK_EQ(disc_open_memory(zeros, 10, &disc), DISC_ERR_FORMAT);

    /* A root directory record that isn't a directory. */
    memcpy(copy, image, size);
    copy[16 * 2048 + 156 + 25] = 0;
    CHECK_EQ(disc_open_memory(copy, size, &disc), DISC_ERR_FORMAT);

    /* A root directory pointing past the end of the image. */
    memcpy(copy, image, size);
    copy[16 * 2048 + 156 + 2] = 0xFF;
    copy[16 * 2048 + 156 + 3] = 0xFF;
    CHECK_EQ(disc_open_memory(copy, size, &disc), DISC_OK);
    CHECK_EQ(disc_find_file(disc, "NICO.DAT", &file), DISC_ERR_FORMAT);
    disc_close(disc);

    /* A directory record shorter than the minimum. */
    memcpy(copy, image, size);
    copy[18 * 2048 + 34 * 2] = 20;
    CHECK_EQ(disc_open_memory(copy, size, &disc), DISC_OK);
    CHECK_EQ(disc_find_file(disc, "NICO.DAT", &file), DISC_ERR_FORMAT);
    disc_close(disc);

    /* A name longer than its record. */
    memcpy(copy, image, size);
    copy[18 * 2048 + 34 * 2 + 32] = 200;
    CHECK_EQ(disc_open_memory(copy, size, &disc), DISC_OK);
    CHECK_EQ(disc_find_file(disc, "NICO.DAT", &file), DISC_ERR_FORMAT);
    disc_close(disc);

    CHECK_EQ(disc_open_memory(NULL, 0, &disc), DISC_ERR_ARGUMENT);
    CHECK_EQ(disc_open("this/file/does/not/exist.iso", &disc), DISC_ERR_IO);
    CHECK(strcmp(disc_status_string(DISC_ERR_FORMAT), "unknown error") != 0);

    free(copy);
    free(image);
}

static void test_file_backend(void)
{
    const char *path = "test_disc_image.iso";
    size_t size;
    unsigned char *image = build_sample(&size);
    FILE *f = fopen(path, "wb");
    DiscImage *disc = NULL;

    CHECK(f != NULL);
    if (!f) {
        free(image);
        return;
    }
    CHECK_EQ(fwrite(image, 1, size, f), size);
    fclose(f);
    CHECK_EQ(disc_open(path, &disc), DISC_OK);
    if (disc) {
        check_contents(disc);
        disc_close(disc);
    }
    remove(path);
    free(image);
}

int main(void)
{
    test_find();
    test_list();
    test_large_directory();
    test_raw_sectors();
    test_malformed();
    test_file_backend();
    return check_finish("test_disc_image");
}
