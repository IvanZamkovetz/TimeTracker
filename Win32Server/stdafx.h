// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
// TODO: reference additional headers your program requires here

#include <boost/chrono.hpp>
#include <boost/thread.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include <vector>

#include "IHook.h"
#include "Task.h"
#include "HookRunner.h"
#include "Recognizer.h"
#include "Server.h"
#include "TimeTracker.h"
#include "Win32Server.h"

