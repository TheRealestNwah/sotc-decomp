#ifndef GAMECORE_BGM_H
#define GAMECORE_BGM_H

/* GAMECORE background music (src/xff/GAMECORE/bgm.c): BGM requests on top of
 * the ADPCM streamer. Structs are padded views: only the fields the group
 * reads are named. */

typedef struct AdpcmScriptWork {
    unsigned char unknown00[0x40];
    int field40;
    unsigned int flags;
} AdpcmScriptWork;
typedef struct AdpcmHandle { int handle; } AdpcmHandle;
typedef union AdpcmSlot AdpcmSlot;
union AdpcmSlot {
    struct {
        int state;
        unsigned char unknown04[0x14];
        AdpcmHandle *adpcm;
        AdpcmScriptWork *script;
        unsigned char unknown20[0x10];
        void (*callback)(AdpcmSlot *);
    } fields;
};
typedef struct AdpcmOrientEntry {
    unsigned char unknown00[0x40];
    AdpcmSlot *slot;
    unsigned char unknown44[0xC];
} AdpcmOrientEntry;
typedef struct AdpcmOrient {
    unsigned char unknown00[0xC];
    int count;
    AdpcmOrientEntry *entries;
} AdpcmOrient;

typedef struct BgmRequest {
    int handle;
    int attr;
    int state;
    float volume;
    float volL;
    float volR;
    float fade;
    int closeHandle;
    int *done;
    unsigned int flags;
    int arg28;
    int arg2C;
    int arg30;
} BgmRequest;

void deleteAdpcmOrient(AdpcmOrient *orient);
BgmRequest *bgmAutoStart(int a0, int attr, int a2, int a3);
BgmRequest *bgmStandbyWithPri(int a0, int attr, int a2, int a3, int priority);
BgmRequest *bgmStandby(int a0, int attr, int a2, int a3);
int bgmChkStandbyComplete(BgmRequest *req);
void bgmPlay(BgmRequest *req, float volume);
void bgmStop(BgmRequest *req, int *done, float time);
int bgmStopChk(int done);
void bgmStopAllAttr(int attr, int time);
void bgmChangeVol(BgmRequest *req, float volL, float volR);
void bgmStartGameOver(void);
void bgmEndGameOver(void);
void bgmStageInit(void);
int CreateBgmThread(void);

#endif /* GAMECORE_BGM_H */
