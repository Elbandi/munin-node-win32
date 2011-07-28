#include "StdAfx.h"
#include "PingMuninNodePlugin.h"
#include <Icmpapi.h>
#include <Winsock2.h>

PingMuninNodePlugin::PingMuninNodePlugin(const std::string &hostName)
{
	ipaddr = inet_addr(hostName.c_str());
	if (ipaddr == INADDR_NONE)
		return;

	hIcmpFile = IcmpCreateFile();
	if (hIcmpFile == INVALID_HANDLE_VALUE)
		return;
	m_Name = "ping_" + hostName;
}

PingMuninNodePlugin::~PingMuninNodePlugin() 
{
	if (hIcmpFile != INVALID_HANDLE_VALUE)
		IcmpCloseHandle(hIcmpFile);
}

int PingMuninNodePlugin::GetConfig(char *buffer, int len) 
{
  int ret = 0;
  struct in_addr HostIP;
  char *host;

  if (ipaddr != INADDR_NONE)
  {
	  HostIP.S_un.S_addr = ipaddr;
	  host = inet_ntoa(HostIP);

	  ret = _snprintf(buffer, len, "graph_title Ping times to %s\n"
		  "graph_args --base 1000 -l 0\n"
		  "graph_vlabel seconds\n"
		  "graph_category network\n"
		  "graph_info This graph shows ping RTT statistics.\n"
		  "ping.label %s\n"
		  "ping.info Ping RTT statistics for %s.\n"
		  "ping.draw LINE2\n"
		  "packetloss.label packet loss\n"
		  "packetloss.graph no\n", host, host, host);
	  buffer += ret;
	  len -= ret;
  }
  strncat(buffer, ".\n", len);

  return 0;
}

int PingMuninNodePlugin::GetValues(char *buffer, int len)
{ 
  int index = 0;
  int ret;
  DWORD dwRetVal = 0;
  char SendData[] = "MUNINNODE";
  LPVOID ReplyBuffer = NULL;
  DWORD ReplySize = 0;
  ULONG RTTSum = 0;
  int PacketLoss = PINGCOUNT;

  ReplySize = sizeof(ICMP_ECHO_REPLY) + sizeof(SendData);
  ReplyBuffer = (VOID*) malloc(ReplySize);
  if (ReplyBuffer != NULL) {
	  for (int count = 0; count < PINGCOUNT; count++) {
		  dwRetVal = IcmpSendEcho(hIcmpFile, ipaddr, SendData, sizeof(SendData), NULL, ReplyBuffer, ReplySize, 1000);
		  if (dwRetVal != 0) {
			  PICMP_ECHO_REPLY pEchoReply = (PICMP_ECHO_REPLY)ReplyBuffer;
			  RTTSum += pEchoReply->RoundTripTime;
			  PacketLoss--;
		  }
	  }
	  ret = _snprintf(buffer, len, "packetloss.value %d\nping.value %f\n", (PacketLoss * 100) / PINGCOUNT, RTTSum / (PINGCOUNT * 1000.0f));
	  len -= ret;
	  buffer += ret;
	  free(ReplyBuffer);
  }

  strncat(buffer, ".\n", len);
  return 0;
}
