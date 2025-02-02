#pragma once

class Person;
typedef int (*sim_func_t)();

int start_ui(sim_func_t simfunc);
void ui_redraw(Person *, int, int *, int);