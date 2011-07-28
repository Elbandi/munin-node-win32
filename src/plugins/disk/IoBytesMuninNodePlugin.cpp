#include "StdAfx.h"
#include "IoBytesMuninNodePlugin.h"

// dunno this is good :(
#define HZ 100

IoBytesMuninNodePlugin::IoBytesMuninNodePlugin() 
{

}

IoBytesMuninNodePlugin::~IoBytesMuninNodePlugin() 
{

}

int IoBytesMuninNodePlugin::GetConfig(char *buffer, int len) 
{
  int ret = 0;

  strncat(buffer, "graph_title IOstat bytes\n"
	  "graph_args --base 1024 -l 0\n"
	  "graph_vlabel bytes / ${graph_period}\n"
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

int IoBytesMuninNodePlugin::GetValues(char *buffer, int len)
{ 
  int index = 0;
  int ret;
  SYSTEM_PERFORMANCE_INFORMATION_ spi = {0};
  NTSTATUS ntret;

  ntret = NtQuerySystemInformation (SystemPerformanceInformation, (PVOID) &spi, sizeof spi, NULL);
  if (ntret == NO_ERROR)
  {
	  ret = _snprintf(buffer, len, "read.value %I64d\nwrite.value %I64d\nother.value %I64d\n", 
		  spi.ReadTransferCount.QuadPart / 1024, spi.WriteTransferCount.QuadPart / 1024, spi.OtherTransferCount.QuadPart / 1024);
	  len -= ret;
	  buffer += ret;
  }
  strncat(buffer, ".\n", len);
  return 0;
}
