#include "main.h"
#include <stdio.h>


//unstable at high dt often requiring substepping
void update_motor(Motor* motor, double voltage_in, double dt) {
    const double physics_dt = 0.00005;
    double accumulated_t = 0;

    while (accumulated_t < dt) {
        motor->back_emf = motor->emf_constant * motor->velocity;
        motor->voltage = voltage_in - motor->back_emf;

        double dIa = (motor->voltage - (motor->resistance * motor->current)) / motor->inductance;
        motor->current += dIa * physics_dt;

        double dOmege = ((motor->torque_constant * motor->current) - (motor->friction * motor->velocity)) / motor->moi;
        motor->velocity += dOmege * physics_dt;
        accumulated_t += physics_dt;
    }
}

MotorDerivatives get_derivatives(Motor* m, double voltage_in, double current, double velocity) {
    MotorDerivatives derivs;
    double voltage = voltage_in - (m->emf_constant * velocity);

    derivs.dI = (voltage - (m->resistance * current)) / m->inductance;
    derivs.dOmega = ((m->torque_constant * current) - (m->friction * velocity)) / m->moi;

    return derivs;
}

//Euler alternative that is more stable at high dt
void update_motor_rk4(Motor* m, double voltage_in, double dt) {
    double i = m->current;
    double w = m->velocity;

    MotorDerivatives k1 = get_derivatives(m, voltage_in, i, w);

    MotorDerivatives k2 = get_derivatives(m, voltage_in, i + k1.dI * dt/2, w + k1.dOmega * dt/2);

    MotorDerivatives k3 = get_derivatives(m, voltage_in, i + k2.dI * dt/2, w + k2.dOmega * dt/2);

    MotorDerivatives k4 = get_derivatives(m, voltage_in, i + k3.dI * dt, w + k3.dOmega * dt);

    m->current += (dt / 6.0) * (k1.dI + 2*k2.dI + 2*k3.dI + k4.dI);
    m->velocity += (dt / 6.0) * (k1.dOmega + 2*k2.dOmega + 2*k3.dOmega + k4.dOmega);

    m->voltage = voltage_in - (m->emf_constant * m->velocity);
    m->back_emf = m->emf_constant * m->velocity;
}

Motor* create_motor(double emf_constant, double torque_constant, double moi, double friction) {
    Motor* motor = malloc(sizeof(struct Motor));
    motor->emf_constant = emf_constant;
    motor->torque_constant = torque_constant;
    motor->inductance = 0.001;
    motor->moi = moi;
    motor->friction = friction;
    motor->last_update = 0;
    motor->voltage = 0;
    motor->velocity = 0;
    motor->current = 0;
    motor->resistance = 0.0328;
    motor->back_emf = 0;
    return motor;
}

int main(void) {
    Motor* motor = create_motor(0.0191, 0.0195, 0.01, 0.000062);
    Motor* motor2 = create_motor(0.0191, 0.0195, 0.01, 0.000062);

    while (1)
    {
        clock_t time = clock();
        double dt = (double)(time - motor->last_update) / CLOCKS_PER_SEC;
        printf("dt: %.2f \n", dt * 1000.0);

        update_motor(motor, 12, dt);
        update_motor_rk4(motor2, 12, dt);

        motor->last_update = time;
        motor2->last_update = time;

        printf("Velocity: %.2f | Voltage: %.2f | Current: %.2f\n",
                        motor->velocity / (M_PI / 30.0) , motor->voltage, motor->current);
        printf("Velocity2: %.2f | Voltage2: %.2f | Current2: %.2f\n",
                        motor2->velocity / (M_PI / 30.0) , motor2->voltage, motor2->current);


        clock_t final = clock();
        double elapsed = (double)(final - time) / CLOCKS_PER_SEC;
        elapsed *= 1000.0;
        sleep_ms(10 - elapsed);
    }

    free(motor);

    return 0;
}
