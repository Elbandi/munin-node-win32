#include "StdAfx.h"
#include "IoOperationMuninNodePlugin.h"

IoOperationMuninNodePlugin::IoOperationMuninNodePlugin() 
{

}

IoOperationMuninNodePlugin::~IoOperationMuninNodePlugin() 
{

}

int IoOperationMuninNodePlugin::GetConfig(char *buffer, int len) 
{
  int ret = 0;

  strncat(buffer, "graph_title IOstat Operation\n"
	  "graph_args --base 1024 -l 0\n"
	  "graph_vlabel operation / ${graph_period}\n"
	  "graph_category disk\n"
	  "graph_info This graph shows the I/O to and from block devices.\n"
	  "read.label read\n"
	  "read.type DERIVE\n"
	  "read.min 0\n"
	  "write.label write\n"
	  "write.type DERIVE\n"
	  "write.min 0\n"
	  "other.label other\n"
	  "other.type DERIVE\n"
	  "other.min 0\n"
	  ".\n", len);

  return 0;
}

int IoOperationMuninNodePlugin::GetValues(char *buffer, int len)
{ 
  int index = 0;
  int ret;
  SYSTEM_PERFORMANCE_INFORMATION_ spi = {0};
  NTSTATUS ntret;

  ntret = NtQuerySystemInformation (SystemPerformanceInformation, (PVOID) &spi, sizeof spi, NULL);
  if (ntret == NO_ERROR)
  {
	  ret = _snprintf(buffer, len, "read.value %u\nwrite.value %u\nother.value %u\n", 
		  spi.ReadOperationCount, spi.WriteOperationCount, spi.OtherOperationCount);
	  len -= ret;
	  buffer += ret;
  }
  strncat(buffer, ".\n", len);
  return 0;
}
