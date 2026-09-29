#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include "offsets.h"
#include "LogicStructs.h"
#include <d3d11.h>
#include <TlHelp32.h>
#include <algorithm>

class RobloxMemory {
private:
    HANDLE hProcess;
    uintptr_t baseAddress;
    DWORD pid;

public:
    RobloxMemory() : hProcess(NULL), baseAddress(0), pid(0) {}

    ~RobloxMemory() {
        if (hProcess) CloseHandle(hProcess);
    }

    bool Initialize() {
        pid = GetRobloxProcessId();
        if (!pid) {
            std::cout << "[-] Roblox process not found!" << std::endl;
            return false;
        }
        std::cout << "[+] Found Roblox process with PID: " << pid << std::endl;

        hProcess = OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, pid);
        if (!hProcess) {
            std::cout << "[-] Failed to open process. Try running as Administrator!" << std::endl;
            return false;
        }
        std::cout << "[+] Opened process successfully!" << std::endl;

        baseAddress = GetRobloxBaseAddress();
        if (!baseAddress) {
            std::cout << "[-] Failed to get base address!" << std::endl;
            return false;
        }
        std::cout << "[+] Base address: 0x" << std::hex << baseAddress << std::dec << std::endl;

        return true;
    }

    template<typename T>
    T Read(uintptr_t address) {
        T value{};
        if (!address || address < 0x10000) return value;
        ReadProcessMemory(hProcess, (LPCVOID)address, &value, sizeof(T), nullptr);
        return value;
    }

    uintptr_t ReadPtr(uintptr_t address) {
        return Read<uintptr_t>(address);
    }

    Vector3 ReadVector3(uintptr_t address) {
        return Read<Vector3>(address);
    }

    
    float ReadFloat(uintptr_t address) {
        return Read<float>(address);
    }

    bool ReadString(uintptr_t address, char* buffer, size_t size) {
        if (!address || address < 0x10000) return false;
        return ReadProcessMemory(hProcess, (LPCVOID)address, buffer, size, nullptr) != 0;
    }

    bool ReadBool(uintptr_t address)
    {
        return Read<bool>(address);
    }

    bool ReadRaw(uintptr_t address, void* buffer, size_t size)
    {
        if (!hProcess || !address)
            return false;

        SIZE_T bytesRead = 0;

        return ReadProcessMemory(
            hProcess,
            (LPCVOID)address,
            buffer,
            size,
            &bytesRead
        ) && bytesRead == size;
    }

    bool write_raw(std::uintptr_t address, const void* buffer, std::size_t size) const
    {
        if (!hProcess || !address)
            return false;
        SIZE_T bytes_written = 0;
        return WriteProcessMemory(hProcess, reinterpret_cast<LPVOID>(address), buffer, size, &bytes_written) && bytes_written == size;
    }

    std::string ReadRobloxString(uintptr_t address)
    {
        if (!address)
            return {};

        int len = Read<int>(address + 0x10);

        if (len <= 0)
            return {};

        if (len > 1000)
            len = 1000;

        uintptr_t str =
            (len >= 16)
            ? Read<uintptr_t>(address)
            : address;

        if (!str)
            return {};

        std::string out(len, '\0');

        if (!ReadRaw(str, out.data(), len))
            return {};

        return out;
    }

    template<typename T>
    bool TryRead(uintptr_t addr, T& out)
    {
        return ReadRaw(addr, &out, sizeof(T));
    }

    template <typename T>
    bool write(std::uintptr_t address, const T& value) const
    {
        return write_raw(address, &value, sizeof(T));
    }



    HANDLE GetProcessHandle() const { return hProcess; }
    uintptr_t GetBaseAddress() const { return baseAddress; }

private:
    DWORD GetRobloxProcessId() {
        HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (snap == INVALID_HANDLE_VALUE) return 0;

        PROCESSENTRY32W entry;
        entry.dwSize = sizeof(entry);

        DWORD foundPid = 0;
        if (Process32FirstW(snap, &entry)) {
            do {
                if (_wcsicmp(entry.szExeFile, L"RobloxPlayerBeta.exe") == 0 ||
                    _wcsicmp(entry.szExeFile, L"Windows10Universal.exe") == 0) {
                    foundPid = entry.th32ProcessID;
                    break;
                }
            } while (Process32NextW(snap, &entry));
        }

        CloseHandle(snap);
        return foundPid;
    }

    uintptr_t GetRobloxBaseAddress() {
        HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);
        if (snap == INVALID_HANDLE_VALUE) return 0;

        MODULEENTRY32W entry;

        entry.dwSize = sizeof(entry);
        uintptr_t base = 0;
        if (Module32FirstW(snap, &entry)) {
            do {
                if (_wcsicmp(entry.szModule, L"RobloxPlayerBeta.exe") == 0 ||
                    _wcsicmp(entry.szModule, L"Windows10Universal.exe") == 0) {
                    base = (uintptr_t)entry.modBaseAddr;
                    break;
                }
            } while (Module32NextW(snap, &entry));
        }

        CloseHandle(snap);
        return base;
    }
};

inline RobloxMemory g_Memory;