/*
*   Copyright (C) {2019.1}  {Djunio - SeiTbNao - Wed}
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see [http://www.gnu.org/licenses/].
*
*/
#pragma once

#include <mutex>
#include <string>
#include <vector>

class LogManager : public Singleton<LogManager> {
public:
    static void Write(const char* message);
    static void WriteFormat(const char* format, ...);
    static void Flush();
    static void SetFlushInterval(DWORD milliseconds);
    static void SetFilePath(const char* path);

protected:
    friend class Singleton<LogManager>;
    LogManager() = default;
    virtual ~LogManager() {}
    LogManager(const LogManager&) = delete;
    LogManager& operator=(const LogManager&) = delete;

private:
    void write(const char* message);
    void flush();
    void setFlushInterval(DWORD milliseconds);
    void setFilePath(const char* path);
    bool shouldFlushLocked(DWORD now) const;

    std::mutex mutex_;
    std::vector<std::string> buffer_;
    std::string filePath_ = "./UIControl.log";
    DWORD flushIntervalMs_ = 5000;
    DWORD lastFlushTick_ = 0;
    static constexpr size_t MaxBufferedLines = 128;
};
