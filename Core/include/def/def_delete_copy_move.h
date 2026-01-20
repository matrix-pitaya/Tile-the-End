#pragma once

#ifndef DELETE_COPY_AND_MOVE
#define DELETE_COPY_AND_MOVE(Class)       \
private:								  \
Class(const Class&) = delete;             \
Class(Class&&) = delete;                  \
Class& operator=(const Class&) = delete;  \
Class& operator=(Class&&) = delete;
#endif