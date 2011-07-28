#include "StdAfx.h"
#include "SwapMuninNodePlugin.h"

SwapMuninNodePlugin::SwapMuninNodePlugin() 
{

}

SwapMuninNodePlugin::~SwapMuninNodePlugin() 
{

}

int SwapMuninNodePlugin::GetConfig(char *buffer, int len) 
{
  int ret = 0;

  strncpy(buffer, "graph_title Swap in/out\n"
	  "graph_args -l 0 --base 1000\n"
	  "graph_vlabel pages per ${graph_period} in (-) / out (+)\n"
	  "graph_category system\n"
	  "swap_in.label swap\n"
	  "swap_in.type DERIVE\n"
	  "swap_in.max 100000\n"
	  "swap_in.min 0\n"
	  "swap_in.graph no\n"
	  "swap_out.label swap\n"
	  "swap_out.type DERIVE\n"
	  "swap_out.max 100000\n"
	  "swap_out.min 0\n"
	  "swap_out.negative swap_in\n"
	  ".\n", len);

  return 0;
}

int SwapMuninNodePlugin::GetValues(char *buffer, int len)
{ 
  int index = 0;
  int ret;
  SYSTEM_PERFORMANCE_INFORMATION_ spi = {0};
  NTSTATUS ntret;

  ntret = NtQuerySystemInformation (SystemPerformanceInformation, (PVOID) &spi, sizeof spi, NULL);
  if (ntret == NO_ERROR)
  {
	  ret = _snprintf(buffer, len, "swap_in.value %u\nswap_out.value %u\n", spi.PagesRead, spi.PagefilePagesWritten);
	  len -= ret;
	  buffer += ret;
  }
  strncat(buffer, ".\n", len);
  return 0;
}
