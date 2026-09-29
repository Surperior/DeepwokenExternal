#pragma once
#include <Windows.h>
#include <cstdint>
#include <string>
#include <memory>
#include <type_traits>
class c_memory
{
public:
    c_memory() = default;
    ~c_memory() = default;
    bool attach(const std::wstring& process_name);
    void detach();
    [[nodiscard]] std::uintptr_t get_base_address() const { return m_base_address; }
    [[nodiscard]] std::uint32_t  get_process_id()    const { return m_process_id; }
    [[nodiscard]] bool           is_attached()       const { return m_process_id != 0; }
    template <typename T>
    T read(std::uintptr_t address) const
    {
        T value{};
        read_raw(address, &value, sizeof(T));
        return value;
    }
    template <typename T>
    bool write(std::uintptr_t address, const T& value) const
    {
        return write_raw(address, &value, sizeof(T));
    }
    std::string read_string(std::uintptr_t address, std::size_t max_length = 256) const;
    std::string read_c_string(std::uintptr_t address, std::size_t max_length = 256) const;
    bool   read_raw(std::uintptr_t address, void* buffer, std::size_t size) const;
    bool   write_raw(std::uintptr_t address, const void* buffer, std::size_t size) const;
private:
    HANDLE          m_process_handle = nullptr;
    std::uintptr_t  m_base_address   = 0;
    std::uint32_t   m_process_id     = 0;
};
inline auto Memory = std::make_unique<c_memory>();

