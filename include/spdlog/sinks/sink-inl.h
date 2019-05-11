// Copyright(c) 2015-present Gabi Melman & spdlog contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include "spdlog/common.h"
#include "spdlog/details/pattern_formatter.h"

SPDLOG_INLINE spdlog::sinks::sink::sink()
    : formatter_{details::make_unique<spdlog::pattern_formatter>()}
{
}

SPDLOG_INLINE spdlog::sinks::sink::sink(std::unique_ptr<spdlog::formatter> formatter)
    : formatter_{std::move(formatter)}
{
}

SPDLOG_INLINE bool spdlog::sinks::sink::should_log(spdlog::level::level_enum msg_level) const
{
    return msg_level >= level_.load(std::memory_order_relaxed);
}

SPDLOG_INLINE void spdlog::sinks::sink::set_level(level::level_enum log_level)
{
    level_.store(log_level);
}

SPDLOG_INLINE spdlog::level::level_enum spdlog::sinks::sink::level() const
{
    return static_cast<spdlog::level::level_enum>(level_.load(std::memory_order_relaxed));
}
