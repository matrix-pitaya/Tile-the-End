#pragma once

#ifndef DECLARE_ENGINE_SUBSYSTEM
#define DECLARE_ENGINE_SUBSYSTEM(Class)         \
    friend class ::Engine::Engine;              \
public:											\
	bool Initialize();							\
	void Release();								\
private:                                        \
    Class() = default;                          \
    ~Class() { Release(); }                     \
    Class(const Class&) = delete;               \
    Class& operator=(const Class&) = delete;    \
    Class(Class&&) = delete;                    \
    Class& operator=(Class&&) = delete;         \
private:                                        \
bool isInitialized = false;						\
bool isReleased = false;
#endif