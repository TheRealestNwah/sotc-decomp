typedef int s128 __attribute__((mode(TI)));

extern s128 D_00040930[];
extern void iosInitPushPosVuSema(void);
extern void InitQuaternionDrive(void);
extern void InitTableSinCos(void);

/* Resets VIF0 and VU0, sends the two-quadword VIF0 init packet, then sets up
   the quaternion stack and the sine table. The empty noreorder block keeps the
   last store out of the call delay slot, as in the original. */
void InitMath(void)
{
    iosInitPushPosVuSema();
    *(volatile int *)0x10003830 = 0;
    *(volatile int *)0x10003820 = 0;
    *(volatile int *)0x10003810 = 1;
    __asm__ __volatile__("cfc2 $8, $vi28\n"
                         "ori $8, $8, 0x2\n"
                         "ctc2 $8, $vi28\n"
                         "sync.p\n"
                         : : : "$8");
    *(volatile s128 *)0x10004000 = D_00040930[0];
    *(volatile s128 *)0x10004000 = D_00040930[1];
    __asm__ __volatile__(".set noreorder\n.set reorder\n");
    InitQuaternionDrive();
    InitTableSinCos();
}
