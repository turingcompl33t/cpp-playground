// Client.cpp
// Client application for unique_handle.

#include <windows.h>

#include "UniqueHandle.h"

int main()
{
	// ctor + dtor
	{
		HANDLE hEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
		unique_handle{ hEvent };
	}
}