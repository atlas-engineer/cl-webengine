#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

EXTERNC int add(int x, int y);
EXTERNC void initialize();

#undef EXTERNC




