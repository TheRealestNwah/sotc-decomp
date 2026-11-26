#ifndef GAMECORE_PERCEPTION_H
#define GAMECORE_PERCEPTION_H

#include "common.h"

/* GAMECORE AI perception (src/xff/GAMECORE/perception.c): sight, hearing and
 * lost-target timers. Structs are padded views: only the fields the group
 * reads are named. */

typedef union {
    s128 q;
    float f[4];
} PercVec4;
typedef union {
    struct { int a, b, c, d; } i;
    float f[4];
} PercRes;
typedef struct {
    char pad0[0x18];
    float lost;
    float h;
    float v;
    float bow;
} PercParam;
typedef struct {
    PercVec4 pos;
    PercVec4 last;
    float hTime;
    float vTime;
    float lostTime;
    int lost;
    PercRes res;
    PercParam *param;
    int unk44;
    void *target;
    char *targetLay;
    float distXZ;
    float dist;
    float bowTime;
} PercWork;

typedef struct {
    char pad[0x134];
    /* The char member lets the stores below alias the pointer, so it is
       reloaded for the second copy, as in the original. */
    union {
        u_long128 *pos;
        char alias;
    } pos;
} PerceptionObj;
typedef struct {
    u_long128 last[2];
    char pad[0x2C];
    PerceptionObj *obj;
} PerceptionWork;

void updatePerceptionWork(void *obj);
int perceptionExec(void *obj, char *w, int *res, float *target);
void createPerceptionWork(void *a, int b);
void setPerceptionParam(void *arg0, int arg1);
int perceptionExec2(void *obj, char *w, void *target);
void forceSetPerceptionWork(void *arg0, void *work);
void forceRenewLastPosPerceptionWork(void *unused, PerceptionWork *work);
int equipmentInvisibilityCloak(int a, int b, int c, int d);

#endif /* GAMECORE_PERCEPTION_H */
