#pragma once

#ifndef DECLARE_SINGLETON_CLASS_R
//宏定义单例模板 请在.h文件类内使用该宏 参数为类名	 注意:请在.cpp文件实现Release函数
#define DECLARE_SINGLETON_CLASS_R(Class)							\
public:																\
	void Release();													\
private:															\
	Class() = default;												\
	~Class() { Release(); }											\
	Class(const Class&) = delete;									\
	Class(Class&&) = delete;										\
	Class& operator=(const Class&) = delete;						\
	Class& operator=(Class&&) = delete;								\
public:																\
	static Class& Instance;											\
private:															\
	static Class instance;											\
	bool isReleased = false;											
#endif


#ifndef DECLARE_SINGLETON_CLASS_RB
//宏定义单例模板 请在.h文件类内使用该宏 参数为类名	 注意:请在.cpp文件实现Bootstrap和Release函数
#define DECLARE_SINGLETON_CLASS_RB(Class)							\
public:																\
	void Release();													\
private:															\
	void Bootstrap();												\
private:															\
	Class() { Bootstrap(); }										\
	~Class() { Release(); }											\
	Class(const Class&) = delete;									\
	Class(Class&&) = delete;										\
	Class& operator=(const Class&) = delete;						\
	Class& operator=(Class&&) = delete;								\
public:																\
	static Class& Instance;											\
private:															\
	static Class instance;											\
	bool isBootstraped = false;										\
	bool isReleased = false;											
#endif


#ifndef DECLARE_SINGLETON_CLASS_RI
//宏定义单例模板 请在.h文件类内使用该宏 参数为类名	 注意:请在.cpp文件实现Initialize和Release函数
#define DECLARE_SINGLETON_CLASS_RI(Class)							\
public:																\
	bool Initialize();												\
	void Release();													\
private:															\
	Class() = default;												\
	~Class() { Release(); }											\
	Class(const Class&) = delete;									\
	Class(Class&&) = delete;										\
	Class& operator=(const Class&) = delete;						\
	Class& operator=(Class&&) = delete;								\
public:																\
	static Class& Instance;											\
private:															\
	static Class instance;											\
	bool isInitialized = false;										\
	bool isReleased = false;											
#endif


#ifndef DECLARE_SINGLETON_CLASS_RBI
//宏定义单例模板 请在.h文件类内使用该宏 参数为类名	 注意:请在.cpp文件实现Bootstrap和Initialize和Release函数
#define DECLARE_SINGLETON_CLASS_RBI(Class)							\
public:																\
	bool Initialize();												\
	void Release();													\
private:															\
	void Bootstrap();												\
private:															\
	Class() { Bootstrap(); }										\
	~Class() { Release(); }											\
	Class(const Class&) = delete;									\
	Class(Class&&) = delete;										\
	Class& operator=(const Class&) = delete;						\
	Class& operator=(Class&&) = delete;								\
public:																\
	static Class& Instance;											\
private:															\
	static Class instance;											\
	bool isBootstraped = false;										\
	bool isInitialized = false;										\
	bool isReleased = false;											
#endif


#ifndef IMPLEMENT_SINGLETON_CLASS
//宏实现单例模板 请在.cpp文件使用该宏 参数为命名空间名 类名 
#define IMPLEMENT_SINGLETON_CLASS(Namespace,Class)					\
Namespace::Class Namespace::Class::instance;						\
Namespace::Class& Namespace::Class::Instance = instance;			
#endif
