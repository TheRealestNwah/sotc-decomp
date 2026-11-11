/* func_0000C668: MATCHES under try_compilers, but xff_splice fails with "word 0 isnt where expected in text.s".
   Cause found: the static function is listed twice in the replacements (same start 0xC630), so the second splice
   pass sees the already-spliced words. Needs a dedupe in tools/xff_splice.py (place_functions/replacements) before enabling. */
#ifdef NONMATCHING
extern void scrRun(void);
extern void usbdevFrameInit(void);

static void func_0000C668(void)
{
    scrRun();
    for (;;) {
        usbdevFrameInit();
        scrRun();
    }
}
#endif
