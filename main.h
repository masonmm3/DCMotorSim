#pragma once
#include "time.h"
#include <stdlib.h>
#include "stdio.h"
#include <stdio.h>
#include <time.h>
#define sleep_ms(ms) \
    do {                                    \
        clock_t _start = clock();           \
        while (((double)(clock() - _start)  \
               / CLOCKS_PER_SEC) * 1000.0 < (ms)); \
    } while (0)

#define M_PI 3.14159265358979323846

typedef struct Motor Motor;
typedef struct MotorDerivatives MotorDerivatives;

struct Motor {
    double voltage;
    double back_emf;
    double current;
    double resistance;
    double inductance;
    double velocity;
    double emf_constant;
    double torque_constant;
    double moi;
    double friction;
    clock_t last_update;
};

struct MotorDerivatives{
    double dI;
    double dOmega;
};
