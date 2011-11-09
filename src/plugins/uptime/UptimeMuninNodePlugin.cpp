#include "StdAfx.h"
#include "UptimeMuninNodePlugin.h"

#if 0
/* Stolen from aMule */
/* This function cannot handle the correct tick, 
   if there was a overflown beforce calling first time this function */
DWORDLONG GetTickCount64_()
{
	// The base value, can store more than 49 days worth of ms.
	static DWORDLONG tick = 0;
	// The current tickcount, may have overflown any number of times.
	static DWORD lastTick = 0;

	DWORD curTick = GetTickCount();

	// Check for overflow
	if ( curTick < lastTick ) {
		// Change the base value to contain the overflown value.
		tick += (DWORDLONG)1 << 32;
	}

	lastTick = curTick;
	return tick + lastTick;
}
#endif

DWORDLONG GetTickCount_64(void)
{
	// Use highres timer for all operations on Windows
	// The Timer starts at system boot and runs (on a Intel Quad core) 
	// with 14 million ticks per second. So it won't overflow for 
	// 35000 years.

	// Convert hires ticks to milliseconds
	static double tickFactor;
	_LARGE_INTEGER li;

	static bool first = true;
	if (first) {
		// calculate the conversion factor for the highres timer
		QueryPerformanceFrequency(&li);
		tickFactor = 1000.0 / li.QuadPart;
		first = false;
	}

	QueryPerformanceCounter(&li);
	return (DWORDLONG)(li.QuadPart * tickFactor);
}

UptimeMuninNodePlugin::UptimeMuninNodePlugin()
{
	GetTickCount64 = (PROCTICKCOUNT)GetProcAddress(GetModuleHandle(_T("Kernel32")), "GetTickCount64");
	if (!GetTickCount64) {
		GetTickCount64 = (PROCTICKCOUNT)GetTickCount_64;
	}
}

UptimeMuninNodePlugin::~UptimeMuninNodePlugin()
{

}

int UptimeMuninNodePlugin::GetConfig(char *buffer, int len) 
{
  strncpy(buffer, "graph_title Uptime\n"
    "graph_category system\n"
    "graph_args --base 1000 -l 0\n"
    "graph_vlabel uptime in days\n"
    "uptime.label uptime\n"
    "uptime.draw AREA\n"
    ".\n", len);

  return 0;
}

int UptimeMuninNodePlugin::GetValues(char *buffer, int len)
{ 
  DWORDLONG tick = GetTickCount64();
  double napok = tick / 86400000.0f ; // 86400 * 1000
  _snprintf(buffer, len, "uptime.value %.2f\n.\n", napok);
  return 0;
}
