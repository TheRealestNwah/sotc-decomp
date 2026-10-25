typedef struct {
    char pad[0xC];
    int option;
    int size;
    int format;
    int flags;
} PcmInputConfig;
extern int B_000E2370;
extern int func_0002ED60(int, int, int, int, int, int, int, int);

int Sg2ExPcmInputOpen(int channel, PcmInputConfig *config)
{
    int inputHalf = B_000E2370 / 2;
    int configHalf = config->size / 2;
    int width = (config->format || config->flags) ? 4 : 2;
    return func_0002ED60(channel, configHalf, inputHalf,
                        config->option, width, config->format, config->flags,
                        config->size);
}
