typedef int Qword __attribute__((mode(TI)));
extern Qword D_00040930[2];
extern void iosInitPushPosVuSema(void);
extern void InitQuaternionDrive(void);
extern void InitTableSinCos(void);
void InitMath(void)
{
    volatile unsigned int *mask;
    volatile unsigned int *mode;
    volatile unsigned int *reset;
    volatile Qword *fifo;
    iosInitPushPosVuSema();
    mask = (volatile unsigned int *)0x10003830;
    mode = (volatile unsigned int *)0x10003820;
    reset = (volatile unsigned int *)0x10003810;
    *mask = 0;
    *mode = 0;
    *reset = 1;
    __asm__ __volatile__("cfc2 $8, $28\n" "ori $8, $8, 2\n" "ctc2 $8, $28\n" "sync.p\n"
        : : : "$8", "memory");
    fifo = (volatile Qword *)0x10004000;
    *fifo = D_00040930[0];
    *fifo = D_00040930[1];
    InitQuaternionDrive();
    InitTableSinCos();
}
