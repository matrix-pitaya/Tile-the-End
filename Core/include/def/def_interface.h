#pragma once

#ifndef DECLARE_INTERFACE
#define DECLARE_INTERFACE(Class)              \
public:                                       \
    Class() = default;                        \
    virtual ~Class() = default;               \
    Class(const Class&) = delete;             \
    Class& operator=(const Class&) = delete;  \
    Class(Class&&) = delete;                  \
    Class& operator=(Class&&) = delete;       
#endif