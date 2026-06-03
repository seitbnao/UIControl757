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
#include "BaseHeader.h"

void LogManager::Write(const char* message) {
    LogManager::instance().write(message);
}

void LogManager::WriteFormat(const char* format, ...) {
    if (!format)
        return;

    char buffer[1024] = { 0 };
    va_list args;
    va_start(args, format);
    vsprintf_s(buffer, sizeof buffer, format, args);
    va_end(args);

    Write(buffer);
}

void LogManager::Flush() {
    LogManager::instance().flush();
}

void LogManager::SetFlushInterval(DWORD milliseconds) {
    LogManager::instance().setFlushInterval(milliseconds);
}

void LogManager::SetFilePath(const char* path) {
    LogManager::instance().setFilePath(path);
}

void LogManager::write(const char* message) {
    if (!message || !message[0])
        return;

    bool flushNow = false;
    {
        std::lock_guard<std::mutex> lock(mutex_);
        buffer_.emplace_back(message);

        auto& line = buffer_.back();
        if (line.empty() || line.back() != '\n')
            line += "\n";

        const auto now = GetTickCount();
        if (lastFlushTick_ == 0)
            lastFlushTick_ = now;

        flushNow = shouldFlushLocked(now);
    }

    if (flushNow)
        flush();
}

void LogManager::flush() {
    std::vector<std::string> pending;
    std::string filePath;

    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (buffer_.empty())
            return;

        pending.swap(buffer_);
        filePath = filePath_;
        lastFlushTick_ = GetTickCount();
    }

    std::ofstream logFile(filePath.c_str(), std::ios_base::app);
    if (!logFile)
        return;

    for (const auto& line : pending)
        logFile << line;
}

void LogManager::setFlushInterval(DWORD milliseconds) {
    std::lock_guard<std::mutex> lock(mutex_);
    flushIntervalMs_ = milliseconds;
}

void LogManager::setFilePath(const char* path) {
    if (!path || !path[0])
        return;

    Flush();

    std::lock_guard<std::mutex> lock(mutex_);
    filePath_ = path;
}

bool LogManager::shouldFlushLocked(DWORD now) const {
    if (buffer_.size() >= MaxBufferedLines)
        return true;

    if (flushIntervalMs_ == 0)
        return false;

    if (lastFlushTick_ == 0)
        return false;

    return now - lastFlushTick_ >= flushIntervalMs_;
}
