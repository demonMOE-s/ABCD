#include "zBG_Timing.h"
#include "zBG_Global.h"

void STDWIN32_CALL zBG_init_timing(void) {
	
	__int64 t64Xsend;
	NativeQueryPerformanceCounter=(pwfun)GetProcAddress(GetModuleHandleA("ntdll.dll"),"NtQueryPerformanceCounter");
	NativeQueryPerformanceCounter(&t64Xsend, &t64Qfreq);
	t64Qfreq /= 60;
	SetThreadAffinityMask(GetCurrentThread(), 1);  
	SetProcessAffinityMask(GetCurrentProcess(), 1);
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_ABOVE_NORMAL);  
	SetPriorityClass(GetCurrentProcess(), ABOVE_NORMAL_PRIORITY_CLASS);
}