
extern int texGetCSM1Idx(int);

/* Build the status palette between entries 0xFC and 0xFD. The alpha byte
 * at entry 0xFF gives the number of interpolation steps. */
void SpriteInitStatusClut(unsigned char *palette)
{
    int end0;
    int end1;
    int end2;
    int end3;
    int start0;
    int start1;
    int start2;
    int start3;
    int destination0;
    int destination1;
    int destination2;
    int destination3;
    int alphaNumerator;
    int entry;
    unsigned char steps;

    entry = 1;
    steps = palette[texGetCSM1Idx(0xFF) * 4 + 3];
    /* Keep the chained initialization: the original evaluates all four indices
     * before storing the channel bytes. */
    palette[texGetCSM1Idx(0) * 4] =
        palette[texGetCSM1Idx(0) * 4 + 1] =
        palette[texGetCSM1Idx(0) * 4 + 2] =
        palette[texGetCSM1Idx(0) * 4 + 3] = 0;
    if (steps != 0) {
        do {
            destination0 = texGetCSM1Idx(entry);
            start0 = texGetCSM1Idx(0xFC);
            end0 = texGetCSM1Idx(0xFD);
            palette[destination0 * 4] = palette[start0 * 4] + ((int) ((palette[end0 * 4] - palette[texGetCSM1Idx(0xFC) * 4]) * entry) / (int) steps);
            destination1 = texGetCSM1Idx(entry);
            start1 = texGetCSM1Idx(0xFC);
            end1 = texGetCSM1Idx(0xFD);
            palette[destination1 * 4 + 1] = (palette[start1 * 4 + 1] + ((int) ((palette[end1 * 4 + 1] - palette[texGetCSM1Idx(0xFC) * 4 + 1]) * entry) / (int) steps));
            destination2 = texGetCSM1Idx(entry);
            start2 = texGetCSM1Idx(0xFC);
            end2 = texGetCSM1Idx(0xFD);
            palette[destination2 * 4 + 2] = (palette[start2 * 4 + 2] + ((int) ((palette[end2 * 4 + 2] - palette[texGetCSM1Idx(0xFC) * 4 + 2]) * entry) / (int) steps));
            destination3 = texGetCSM1Idx(entry);
            start3 = texGetCSM1Idx(0xFC);
            end3 = texGetCSM1Idx(0xFD);
            alphaNumerator = (palette[end3 * 4 + 3] - palette[texGetCSM1Idx(0xFC) * 4 + 3]) * entry;
            entry += 1;
            palette[destination3 * 4 + 3] = (palette[start3 * 4 + 3] + (alphaNumerator / (int) steps));
        } while ((int) steps >= entry);
    }
}
