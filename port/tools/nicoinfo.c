/*
 * nicoinfo: prints the NICO.DAT table of contents of the owner's Disc image.
 *
 *   nicoinfo <disc image> [--all]
 *
 * Without --all, long tables are summarized. Nothing is extracted.
 */
#include "disc_image.h"
#include "nicodat.h"

#include <stdio.h>
#include <string.h>

static int list_root(void *context, const char *name, const DiscFile *file, int is_directory)
{
    (void)context;
    printf("  %-24s %s lsn %-8u %10u bytes\n", name, is_directory ? "dir " : "file", file->lsn, file->size);
    return 0;
}

static void print_records(const char *label, const NicoRecord *records, uint32_t count, int all)
{
    uint32_t shown = all || count <= 8 ? count : 8;
    printf("    %s: %u\n", label, count);
    for (uint32_t i = 0; i < shown; i++)
        printf("      [%u] sector %u, size %u\n", i, records[i].sector, records[i].size);
    if (shown < count)
        printf("      ... %u more\n", count - shown);
}

int main(int argc, char **argv)
{
    DiscImage *disc = NULL;
    NicoArchive *a = NULL;
    DiscFile file;
    DiscStatus disc_status;
    NicoStatus status;
    int all = argc > 2 && strcmp(argv[2], "--all") == 0;

    if (argc < 2) {
        fprintf(stderr, "usage: %s <disc image> [--all]\n", argv[0]);
        return 2;
    }
    disc_status = disc_open(argv[1], &disc);
    if (disc_status != DISC_OK) {
        fprintf(stderr, "%s: %s\n", argv[1], disc_status_string(disc_status));
        return 1;
    }
    printf("%s: %u sectors of %u bytes\n", argv[1], disc_sector_count(disc), disc_raw_sector_size(disc));
    printf("root directory:\n");
    disc_list_directory(disc, "\\", list_root, NULL);

    status = nico_open_disc(disc, &a, &file);
    if (status != NICO_OK) {
        fprintf(stderr, "NICO.DAT: %s\n", nico_status_string(status));
        disc_close(disc);
        return 1;
    }
    printf("\nNICO.DAT: lsn %u, %u bytes, header %llu bytes\n", file.lsn, file.size,
        (unsigned long long)a->header_size);
    printf("  boot: sector %u, size %u\n", a->boot.sector, a->boot.size);
    printf("  root: sector %u, size %u\n", a->root.sector, a->root.size);

    printf("  segment types: %u\n", a->segment_type_count);
    for (uint32_t i = 0; i < a->segment_type_count; i++) {
        const NicoSegmentType *t = &a->segment_types[i];
        printf("  - %s: %u index entries\n", t->name, t->index_count);
        print_records("files", t->files, t->file_count, all);
        print_records("localized", t->localized, t->localized_count, all);
    }

    printf("  maps: %u\n", a->map_count);
    for (uint32_t i = 0; i < a->map_count; i++) {
        const NicoMap *m = &a->maps[i];
        printf("  - %s: %u tex segs\n", m->name, m->tex_seg_count);
        for (uint32_t d = 0; d < 3; d++)
            for (uint32_t v = 0; v < 2; v++) {
                char label[32];
                snprintf(label, sizeof label, "data type %u variant %u", d, v);
                print_records(label, m->data_type[d].variant[v], m->data_type[d].count, all);
            }
    }

    printf("  ADPCM:\n");
    print_records("entries", a->adpcm, a->adpcm_count, all);
    printf("  direct files:\n");
    print_records("entries", a->direct, a->direct_count, all);
    printf("  special files: %u\n", a->special_count);
    for (uint32_t i = 0; i < a->special_count; i++)
        printf("  - %s: value %u, %u bytes\n", a->special[i].name, a->special[i].value, a->special[i].data_size);

    nico_free(a);
    disc_close(disc);
    return 0;
}
