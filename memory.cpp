#include "memory.h"
#include <TlHelp32.h>
#include <algorithm>
bool c_memory::attach(const std::wstring& process_name)
{
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE)
        return false;
    PROCESSENTRY32 entry{};
    entry.dwSize = sizeof(entry);
    bool found = false;

    if (Process32First(snapshot, &entry))
    {
        do
        {
            if (process_name == entry.szExeFile)
            {
                m_process_id = entry.th32ProcessID;
                found = true;
                break;
            }
        } while (Process32Next(snapshot, &entry));
    }

    CloseHandle(snapshot);
    if (!found)
        return false;
    m_process_handle = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION | PROCESS_QUERY_INFORMATION, FALSE, m_process_id);
    if (!m_process_handle)
        return false;
    HANDLE module_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, m_process_id);
    if (module_snapshot == INVALID_HANDLE_VALUE)
        return false;
    MODULEENTRY32 module_entry{};
    module_entry.dwSize = sizeof(module_entry);
    if (Module32First(module_snapshot, &module_entry))
    {
        m_base_address = reinterpret_cast<std::uintptr_t>(module_entry.modBaseAddr);
    }
    CloseHandle(module_snapshot);
    return m_base_address != 0;
}

void c_memory::detach()
{   
    if (m_process_handle)
    {
        CloseHandle(m_process_handle);
        m_process_handle = nullptr;
    }
    m_process_id = 0;
    m_base_address = 0;
}
bool c_memory::read_raw(std::uintptr_t address, void* buffer, std::size_t size) const
{
    if (!m_process_handle || !address)
        return false;
    SIZE_T bytes_read = 0;
    return ReadProcessMemory(m_process_handle, reinterpret_cast<LPCVOID>(address), buffer, size, &bytes_read) && bytes_read == size;
}
bool c_memory::write_raw(std::uintptr_t address, const void* buffer, std::size_t size) const
{
    if (!m_process_handle || !address)
        return false;
    SIZE_T bytes_written = 0;
    return WriteProcessMemory(m_process_handle, reinterpret_cast<LPVOID>(address), buffer, size, &bytes_written) && bytes_written == size;
}
std::string c_memory::read_string(std::uintptr_t address, std::size_t max_length) const
{
    auto string_length = read<std::int32_t>(address + 0x10);
    if (string_length <= 0)
        return {};
    if (string_length > 1000) 
        string_length = 1000;
    int read_len = (std::min)(static_cast<int>(string_length), static_cast<int>(max_length));
    std::uintptr_t string_address = (string_length >= 16)
        ? read<std::uintptr_t>(address)
        : address;
    if (!string_address)
        return {};
    std::string result(read_len, '\0');
    if (!read_raw(string_address, result.data(), read_len))
        return {};
    return result;
}
std::string c_memory::read_c_string(std::uintptr_t address, std::size_t max_length) const
{
    std::string result(max_length, '\0');
    if (!read_raw(address, result.data(), max_length))
        return {};
    auto pos = result.find('\0');
    if (pos != std::string::npos)
        result.resize(pos);
    return result;
}

