typedef struct {
    float x;
    float y;
    char pad[8];
} GazeChannel;

typedef struct {
    char pad[0x334];
    GazeChannel *gaze;
} CharacterClass;

void SetCharacterClassGazeAdditionChannelInfo(CharacterClass *chr, unsigned int *channel, float x, float y)
{
    chr->gaze[(*channel >> 18) & 0xFFF].y = y;
    chr->gaze[(*channel >> 18) & 0xFFF].x = x;
}
