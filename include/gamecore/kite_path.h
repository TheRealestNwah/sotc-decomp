#ifndef GAMECORE_KITE_PATH_H
#define GAMECORE_KITE_PATH_H

#include "common.h"

/* GAMECORE kite path work (src/xff/GAMECORE/kite_path.c): path points for
 * the small animals and the leader/child path checks. Helper unions and
 * views of other groups' objects stay local to kite_path.c. Structs are
 * padded views: only the fields the group reads are named. */

typedef float Vec4[4] __attribute__((aligned(16)));

typedef struct {
    s128 pos;
    int a;
    int b;
    int c;
    int pad;
} KitePathPoint;

typedef struct {
    KitePathPoint pts[4];
    s128 pos;
    float x;
    float y;
    int s98;
    int list[10];
    int count;
    void *obj;
    int padcc;
} KiteSub;

typedef struct {
    int a;
    int b;
    int pad8[2];
    KitePathPoint pts[6];
    s128 pos;
    float x;
    float y;
    int e8;
    int ec;
    void *obj;
    int padf4[11];
    KiteSub sub;
    char special[1];
} KitePathWork;

/* func_000AD410 */

typedef struct {
    long long a;
    long long b;
    int idx;
    int pad14;
    long long d;
} PathPt;

typedef struct {
    PathPt cur;
    PathPt next;
    PathPt saveCur;
    PathPt saveNext;
    char pad80[0x18];
    int flag;
} PathWork;

typedef struct {
    int kind;
    char pad04[0xFC];
    char area[0x20];
    PathWork pw;
    char padBC[0x1F0 - 0x120 - sizeof(PathWork)];
    char special[1];
} Kite;

/* KiteSpecial_SetNewPathPoint */

typedef struct {
    Vec4 center;
    float radius;
    float height;
} KiteArea;

typedef struct {
    Vec4 pos;
    int area;
    int pt;
    int idx;
    int pad;
} PassPt;

typedef struct {
    PassPt p[2];
} PassPair;

typedef struct {
    int x0;
    int x4;
    int x8[2];
    PassPair cur;
    PassPair prev;
    PassPair save;
} PassWork;

void Kite_InitKitePathWork(KitePathWork *w, void *obj, float x, float y);
void KiteSpecial_SetNewPathPoint(float *pt, int unused, char *kite, float *target);
int Kite_GetPassageWork(int unused, void *owner, int *kite, PassWork *w, int flag);
void Kite_InitSpecialPathWork(void *layout);
int AI_CheckPathPoint(void *obj, float *pos, float r, float h);
int Kite_CmpPathPoint(char *a, char *b);
void Kite_InitKitePathPoint(KitePathPoint *p);
void AI_UpdateLeaderPathWork(void *path, char *w);
void AI_UpdateChildPathWork(char *work);
void Kite_InitKiteAdvertisePathWork(void *arg0);

#endif /* GAMECORE_KITE_PATH_H */
