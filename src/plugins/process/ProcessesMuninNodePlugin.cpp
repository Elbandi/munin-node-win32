/* This file is part of munin-node-win32
 * Copyright (C) 2006-2007 Jory Stone (jcsston@jory.info)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "StdAfx.h"
#include "ProcessesMuninNodePlugin.h"
#include <Psapi.h>

ProcessesMuninNodePlugin::ProcessesMuninNodePlugin()
{
}

ProcessesMuninNodePlugin::~ProcessesMuninNodePlugin()
{
}

int ProcessesMuninNodePlugin::GetConfig(char *buffer, int len) 
{
  strncpy(buffer, "graph_title Number of Processes\n"
    "graph_args --base 1000 -l 0\n"
    "graph_vlabel number of processes\n"
    "graph_category processes\n"
    "graph_info This graph shows the number of processes and threads in the system.\n"
    "processes.label processes\n"
    "processes.draw LINE2\n"
    "processes.info The current number of processes.\n"
    "threads.label threads\n"
    "threads.draw LINE1\n"
    "threads.info The current number of threads.\n"
    "handles.label handles\n"
    "handles.draw LINE1\n"
    "handles.info The current number of handles.\n"
    ".\n", len);

  return 0;
}

int ProcessesMuninNodePlugin::GetValues(char *buffer, int len) 
{ 
  PERFORMANCE_INFORMATION pi;

  if (GetPerformanceInfo(&pi, sizeof(PERFORMANCE_INFORMATION))) {
	  int count;
	  count = _snprintf(buffer, len, "processes.value %u\nthreads.value %u\nhandles.value %u\n", pi.ProcessCount, pi.ThreadCount, pi.HandleCount);
	  buffer = buffer + count;
	  len -= count;
  }

  strncat(buffer, ".\n", len);
  return 0;
}
