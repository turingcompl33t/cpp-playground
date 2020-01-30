// UniqueHandle.cpp
// std::unique_ptr-like functionality for Windows handles.

#include <windows.h>

#include "UniqueHandle.h"

unique_handle::unique_handle(const HANDLE& h)
	: handle{h}
{}

unique_handle::~unique_handle()
{
	if (INVALID_HANDLE_VALUE != handle && NULL != handle)
	{
		CloseHandle(handle);
	}
}

unique_handle::unique_handle(unique_handle&& rhs)
{
	this->handle = rhs.handle;
	rhs.handle = INVALID_HANDLE_VALUE;
}

unique_handle& unique_handle::operator=(unique_handle&& rhs)
{
	this->handle = rhs.handle;
	rhs.handle = INVALID_HANDLE_VALUE;
	return *this;
}

