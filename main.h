#pragma once
#include "time.h"
#include <stdlib.h>
#include "stdio.h"
#include <stdio.h>
#include <time.h>
#ifdef _WIN32
    #include <windows.h>
    #define sleep_ms(ms) Sleep(ms)
#else
    #include <unistd.h>
    #define sleep_ms(ms) usleep((ms) * 1000)
#endif

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
