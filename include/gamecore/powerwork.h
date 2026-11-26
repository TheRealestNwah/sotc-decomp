#ifndef GAMECORE_POWERWORK_H
#define GAMECORE_POWERWORK_H

/* GAMECORE player power work (src/xff/GAMECORE/powerwork.c): HP, grip, O2
 * and attack power. Structs are padded views: only the fields the group reads
 * are named. The gcGlobalVar view stays local to powerwork.c. */

typedef struct {
    char pad[0xC];
    int n;
    unsigned int *tab;
} MotList;
typedef struct {
    int cur;
    int next;
    char pad[0x14];
    float speed;
} AnimClass;

int updatePowerWork(int obj, float heap, float heap2, float jump);
int chkMotionList(void *motion, char *list);
float getPlayerHp(void);
void setPlayerHp(float hp);
void addPlayerHp(float add);
float _getPlayerHpRatio(void);
float getPlayerMaxHp(void);
void setPlayerMaxHp(float hp);
void addPlayerMaxHp(float add);
float getPlayerGrip(void);
void setPlayerGrip(float g);
void addPlayerGrip(float add);
float getPlayerMaxGrip(void);
void setPlayerMaxGrip(float grip);
void addPlayerMaxGrip(float add);
float getPlayerMaxGripRatio(void);
float getPlayerO2(void);
void setPlayerO2(float fparg0);
void addPlayerO2(float add);
void initPowerWork(void);
void resetAttackPower(void);
float getAttackPowerRatio(void);

#endif /* GAMECORE_POWERWORK_H */
