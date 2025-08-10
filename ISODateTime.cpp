//
// Created by Bijumon Chettipparambil Pavanajan on 09/08/2025.
//

#include "ISODateTime.h"
#include <ctime>
#include <sstream>
#include <iomanip>

/**
 * @brief Convert a time_t value into a std::tm in local time, in a thread-safe manner.
 *
 * This function wraps platform-specific thread-safe variants:
 * - Windows: localtime_s
 * - POSIX (Linux, macOS, etc.): localtime_r
 *
 * @param t The time value to convert.
 * @return A std::tm structure containing the local time representation.
 */
static std::tm to_local_tm(std::time_t t) {
    std::tm tm{};
#if defined(_WIN32) || defined(_WIN64)
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm); // POSIX: time_t* first, tm* second
#endif
    return tm;
}

/**
 * @brief Convert a time_t value into a std::tm in UTC time, in a thread-safe manner.
 *
 * This function wraps platform-specific thread-safe variants:
 * - Windows: gmtime_s
 * - POSIX (Linux, macOS, etc.): gmtime_r
 *
 * @param t The time value to convert.
 * @return A std::tm structure containing the UTC time representation.
 */
static std::tm to_utc_tm(std::time_t t) {
    std::tm tm{};
#if defined(_WIN32) || defined(_WIN64)
    gmtime_s(&tm, &t);
#else
    gmtime_r(&t, &tm); // POSIX: time_t* first, tm* second
#endif
    return tm;
}

// ---------- Public functions ----------

/**
 * @brief Get the ISO 8601 formatted date (YYYY-MM-DD) from a given time_point or from the current system time.
 * @param time_point Optional system_clock::time_point. If not provided, the current system time is used.
 * @return ISO 8601 date string.
 */
std::string ISODateTime::get_current_iso_date(const std::optional<std::chrono::time_point<std::chrono::system_clock>>& time_point)
{
    const auto now = get_input_time_point_or_current_system_time(time_point);
    const auto seconds = std::chrono::system_clock::to_time_t(now);
    const auto tm = to_local_tm(seconds);
    std::ostringstream iso_date;
    iso_date << std::put_time(&tm, "%F");
    return iso_date.str();
}

/**
 * @brief Get the ISO 8601 formatted date and time (YYYY-MM-DDTHH:MM:SS) from a given time_point or from the current system time.
 * @param time_point Optional system_clock::time_point. If not provided, the current system time is used.
 * @return ISO 8601 date-time string.
 */
std::string ISODateTime::get_current_iso_date_time(const std::optional<std::chrono::time_point<std::chrono::system_clock>>& time_point)
{
    const auto now = get_input_time_point_or_current_system_time(time_point);
    const auto seconds = std::chrono::system_clock::to_time_t(now);
    const auto tm = to_local_tm(seconds);
    std::ostringstream iso_date_time;
    iso_date_time << std::put_time(&tm, "%FT%H:%M:%S");
    return iso_date_time.str();
}

/**
 * @brief Get the ISO 8601 formatted date, time, and milliseconds (YYYY-MM-DDTHH:MM:SS.mmm)
 *        from a given time_point or from the current system time.
 * @param time_point Optional system_clock::time_point. If not provided, the current system time is used.
 * @return ISO 8601 timestamp string with milliseconds precision.
 */
std::string ISODateTime::get_current_iso_date_timestamp(const std::optional<std::chrono::time_point<std::chrono::system_clock>>& time_point)
{
    const auto now = get_input_time_point_or_current_system_time(time_point);
    const auto seconds = std::chrono::system_clock::to_time_t(now);
    const auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
    const auto tm = to_local_tm(seconds);

    std::ostringstream iso_date_timestamp;
    iso_date_timestamp << std::put_time(&tm, "%FT%H:%M:%S") << '.' << get_formatted_milliseconds(milliseconds);
return iso_date_timestamp.str();
}

/**
 * @brief Get the ISO 8601 formatted date (YYYY-MM-DD) for the current system time.
 * @return ISO 8601 date string.
 */
std::string ISODateTime::get_current_iso_date()
{
    return get_current_iso_date(std::nullopt);
}

/**
 * @brief Get the ISO 8601 formatted date and time (YYYY-MM-DDTHH:MM:SS) for the current system time.
 * @return ISO 8601 date-time string.
 */
std::string ISODateTime::get_current_iso_date_time()
{
    return get_current_iso_date_time(std::nullopt);
}

/**
 * @brief Get the ISO 8601 formatted date, time, and milliseconds (YYYY-MM-DDTHH:MM:SS.mmm)
 *        for the current system time.
 * @return ISO 8601 timestamp string with milliseconds precision.
 */
std::string ISODateTime::get_current_iso_date_timestamp()
{
    return get_current_iso_date_timestamp(std::nullopt);
}

/**
 * @brief Get the ISO 8601 formatted UTC date (YYYY-MM-DD) from a given time_point or from the current system time.
 * @param time_point Optional system_clock::time_point. If not provided, the current system time is used.
 * @return ISO 8601 date string.
 */
std::string ISODateTime::get_current_utc_iso_date(const std::optional<std::chrono::time_point<std::chrono::system_clock>>& time_point)
{
    const auto now = get_input_time_point_or_current_system_time(time_point);
    const auto seconds = std::chrono::system_clock::to_time_t(now);
    const auto tm = to_utc_tm(seconds);
    std::ostringstream iso_date;
    iso_date << std::put_time(&tm, "%F");
    return iso_date.str();
}

/**
 * @brief Get the ISO 8601 formatted UTC date and time (YYYY-MM-DDTHH:MM:SS) from a given time_point or from the current system time.
 * @param time_point Optional system_clock::time_point. If not provided, the current system time is used.
 * @return ISO 8601 date-time string.
 */
std::string ISODateTime::get_current_utc_iso_date_time(const std::optional<std::chrono::time_point<std::chrono::system_clock>>& time_point)
{
    const auto now = get_input_time_point_or_current_system_time(time_point);
    const auto seconds = std::chrono::system_clock::to_time_t(now);
    const auto tm = to_utc_tm(seconds);
    std::ostringstream iso_date_time;
    iso_date_time << std::put_time(&tm, "%FT%H:%M:%S") << 'Z';
    return iso_date_time.str();
}

/**
 * @brief Get the ISO 8601 formatted UTC date, time, and milliseconds (YYYY-MM-DDTHH:MM:SS.mmm)
 *        from a given time_point or from the current system time.
 * @param time_point Optional system_clock::time_point. If not provided, the current system time is used.
 * @return ISO 8601 timestamp string with milliseconds precision.
 */
std::string ISODateTime::get_current_utc_iso_date_timestamp(const std::optional<std::chrono::time_point<std::chrono::system_clock>>& time_point)
{
    const auto now = get_input_time_point_or_current_system_time(time_point);
    const auto seconds = std::chrono::system_clock::to_time_t(now);
    const auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
    const auto tm = to_utc_tm(seconds);

    std::ostringstream iso_date_timestamp;
    iso_date_timestamp << std::put_time(&tm, "%FT%H:%M:%S") << '.' << get_formatted_milliseconds(milliseconds) << 'Z';
    return iso_date_timestamp.str();
}

/**
 * @brief Get the ISO 8601 formatted UTC date (YYYY-MM-DD) for the current system time.
 * @return ISO 8601 date string.
 */
std::string ISODateTime::get_current_utc_iso_date()
{
    return get_current_utc_iso_date(std::nullopt);
}

/**
 * @brief Get the ISO 8601 formatted UTC date and time (YYYY-MM-DDTHH:MM:SS) for the current system time.
 * @return ISO 8601 date-time string.
 */
std::string ISODateTime::get_current_utc_iso_date_time()
{
    return get_current_utc_iso_date_time(std::nullopt);
}

/**
 * @brief Get the ISO 8601 formatted UTC date, time, and milliseconds (YYYY-MM-DDTHH:MM:SS.mmm)
 *        for the current system time.
 * @return ISO 8601 timestamp string with milliseconds precision.
 */
std::string ISODateTime::get_current_utc_iso_date_timestamp()
{
    return get_current_utc_iso_date_timestamp(std::nullopt);
}

// ---------- Private functions ----------

/**
 * @brief Return the provided time_point, or the current system time if none was given.
 * @param time_point Optional system_clock::time_point.
 * @return The provided time_point or the current system time.
 */
std::chrono::time_point<std::chrono::system_clock> ISODateTime::get_input_time_point_or_current_system_time(const std::optional<std::chrono::time_point<std::chrono::system_clock>>& time_point) noexcept
{
    if (time_point)
        return *time_point;
    return std::chrono::system_clock::now();
}

/**
 * @brief Format milliseconds as a three-digit string with leading zeros if necessary.
 * @param milliseconds Millisecond duration to format.
 * @return A zero-padded 3-digit string representation of the milliseconds.
 */
std::string ISODateTime::get_formatted_milliseconds(const std::chrono::milliseconds& milliseconds)
{
    std::ostringstream ms_formatter;
    ms_formatter << std::setw(3) << std::setfill('0') << milliseconds.count();
    return ms_formatter.str();
}
