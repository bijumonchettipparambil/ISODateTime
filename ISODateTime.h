#ifndef ISODATETIME_LIBRARY_H
#define ISODATETIME_LIBRARY_H

#include <string>
#include <chrono>
#include <optional>

class ISODateTime {
    public:
    // Prevent instantiation
    ISODateTime() = delete;
    ~ISODateTime() = default;
    // Static Public functions
    [[nodiscard]] static std::string get_current_iso_date(const std::optional<std::chrono::time_point<std::chrono::system_clock>>&); // Get current ISO Date from a time_point
    [[nodiscard]] static std::string get_current_iso_date_time(const std::optional<std::chrono::time_point<std::chrono::system_clock>>&); // Get current ISO Date and Time from a time_point
    [[nodiscard]] static std::string get_current_iso_date_timestamp(const std::optional<std::chrono::time_point<std::chrono::system_clock>>&); // Get current ISO Date and Timestamp from a time_point

    [[nodiscard]] static std::string get_current_iso_date(); // Get current ISO Date
    [[nodiscard]] static std::string get_current_iso_date_time(); // Get current ISO Date and Time
    [[nodiscard]] static std::string get_current_iso_date_timestamp(); // Get current ISO Date and Timestamp

    [[nodiscard]] static std::string get_current_utc_iso_date(const std::optional<std::chrono::time_point<std::chrono::system_clock>>&); // Get current ISO Date from a time_point
    [[nodiscard]] static std::string get_current_utc_iso_date_time(const std::optional<std::chrono::time_point<std::chrono::system_clock>>&); // Get current ISO Date and Time from a time_point
    [[nodiscard]] static std::string get_current_utc_iso_date_timestamp(const std::optional<std::chrono::time_point<std::chrono::system_clock>>&); // Get current ISO Date and Timestamp from a time_point

    [[nodiscard]] static std::string get_current_utc_iso_date(); // Get current ISO Date
    [[nodiscard]] static std::string get_current_utc_iso_date_time(); // Get current ISO Date and Time
    [[nodiscard]] static std::string get_current_utc_iso_date_timestamp(); // Get current ISO Date and Timestamp

    private:
    // Static Private functions
    static std::chrono::time_point<std::chrono::system_clock> get_input_time_point_or_current_system_time(const std::optional<std::chrono::time_point<std::chrono::system_clock>>&) noexcept;
    static std::string get_formatted_milliseconds(const std::chrono::milliseconds&); // format

};

#endif //ISODATETIME_LIBRARY_H