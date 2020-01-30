// UniqueHandle.h
// std::unique_ptr-like functionality for Windows handles.

#include <windows.h>

class unique_handle
{
public:
	unique_handle(const HANDLE& h);
	~unique_handle();

	// non-copyable type
	unique_handle(const unique_handle& rhs) = delete;
	unique_handle& operator=(const unique_handle& rhs) = delete;

	unique_handle(unique_handle&& rhs);
	unique_handle& operator=(unique_handle&& rhs);

private:
	HANDLE handle;
};