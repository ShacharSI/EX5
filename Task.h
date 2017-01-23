//
// Created by sha on 1/23/17.
//

#ifndef EX3_TM_TASK_H
#define EX3_TM_TASK_H


class Task {
public:
    Task(void(*fn_ptr)(void*),void*arg);

    ~Task();

    void operator()(); // functor
private:
    void (*m_fn_ptr)(void *);

    void *m_arg;

};


#endif //EX3_TM_TASK_H
