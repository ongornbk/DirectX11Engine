#include "CPU.h"
#include <windows.h>

static ULARGE_INTEGER lastCPU, lastSysCPU, lastUserCPU;
static int numProcessors;
static HANDLE self;

void _cdecl Initialize_CPU()
{
	SYSTEM_INFO sysInfo;
	FILETIME ftime, fsys, fuser;

	GetSystemInfo(&sysInfo);
	numProcessors = sysInfo.dwNumberOfProcessors;

	GetSystemTimeAsFileTime(&ftime);
	memcpy(&lastCPU, &ftime, sizeof(FILETIME));

	self = GetCurrentProcess();
	GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
	memcpy(&lastSysCPU, &fsys, sizeof(FILETIME));
	memcpy(&lastUserCPU, &fuser, sizeof(FILETIME));
}


double _cdecl Get_CPU()
{

FILETIME ftime, fsys, fuser;
ULARGE_INTEGER now, sys, user;
float percent;

	GetSystemTimeAsFileTime(&ftime);
	(void)memcpy(&now, &ftime, sizeof(FILETIME));
	(void)GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
	(void)memcpy(&sys, &fsys, sizeof(FILETIME));
	(void)memcpy(&user, &fuser, sizeof(FILETIME));
	percent = (float)(sys.QuadPart - lastSysCPU.QuadPart) + (user.QuadPart - lastUserCPU.QuadPart);
	percent /= (now.QuadPart - lastCPU.QuadPart);
	percent /= numProcessors;
	lastCPU = now;
	lastUserCPU = user;
	lastSysCPU = sys;
	return percent;
}