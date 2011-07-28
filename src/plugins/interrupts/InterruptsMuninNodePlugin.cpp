#include "StdAfx.h"
#include "InterruptsMuninNodePlugin.h"

InterruptsMuninNodePlugin::InterruptsMuninNodePlugin() 
{

}

InterruptsMuninNodePlugin::~InterruptsMuninNodePlugin() 
{

}

int InterruptsMuninNodePlugin::GetConfig(char *buffer, int len) 
{
  int ret = 0;

  strncpy(buffer, "graph_title Interrupts & context switches\n"
	  "graph_args --base 1000 -l 0\n"
	  "graph_vlabel interrupts & ctx switches / ${graph_period}\n"
	  "graph_category system\n"
	  "graph_info This graph shows the number of interrupts and context switches on the system. These are typically high on a busy system.\n"
	  "intr.info Interrupts are events that alter sequence of instructions executed by a processor. They can come from either hardware (exceptions, NMI, IRQ) or software.\n"
	  "ctx.info A context switch occurs when a multitasking operatings system suspends the currently running process, and starts executing another.\n"
	  "intr.label interrupts\n"
	  "ctx.label context switches\n"
	  "intr.type DERIVE\n"
	  "ctx.type DERIVE\n"
	  "intr.max 100000\n"
	  "ctx.max 100000\n"
	  "intr.min 0\n"
	  "ctx.min 0\n"
	  ".\n", len);

  return 0;
}

int InterruptsMuninNodePlugin::GetValues(char *buffer, int len)
{ 
	int index = 0;
	int ret;
	unsigned long interrupt_count = 0UL, context_switches = 0UL;
	SYSTEM_PERFORMANCE_INFORMATION_ spi = {0};
	NTSTATUS ntret;
	SYSTEM_PROCESSOR_TIMES spt[32];

	SYSTEM_INFO SystemInfo;
	GetSystemInfo(&SystemInfo);

	/* We have array for 32 processor only :( */
	if (SystemInfo.dwNumberOfProcessors <= 32) {

		ntret = NtQuerySystemInformation (SystemProcessorPerformanceInformation, (PVOID) spt,
			sizeof spt[0] * SystemInfo.dwNumberOfProcessors, NULL);
		if (ntret == NO_ERROR)
		{
			for (unsigned int i = 0; i < SystemInfo.dwNumberOfProcessors; i++)
			{
				interrupt_count += spt[i].InterruptCount;
			}
			ret = _snprintf(buffer, len, "intr.value %u\n", interrupt_count);
			len -= ret;
			buffer += ret;
		}  
		ntret = NtQuerySystemInformation (SystemPerformanceInformation, (PVOID) &spi, sizeof spi, NULL);
		if (ntret == NO_ERROR)
		{
			ret = _snprintf(buffer, len, "ctx.value %u\n", spi.ContextSwitches);
			len -= ret;
			buffer += ret;
		}
	}
  strncat(buffer, ".\n", len);
  return 0;
}
