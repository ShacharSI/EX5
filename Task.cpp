//
// Created by sha on 1/23/17.
//

#include "Task.h"

Task::Task(void(*fn_ptr)(void *), void *arg) : m_fn_ptr(fn_ptr), m_arg(arg) {}

Task::~Task() {}

void Task::operator()()
{
    (*m_fn_ptr)(m_arg);
}