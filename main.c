#include "main.h"



void update_motor(Motor* motor, double voltage_in, double dt) {
    motor->back_emf = motor->emf_constant * motor->velocity;
    motor->voltage = voltage_in - motor->back_emf;

    double dIa = (motor->voltage - (motor->resistance * motor->current)) / motor->inductance;
    motor->current += dIa * dt;

    double dOmege = ((motor->torque_constant * motor->current) - (motor->friction * motor->velocity)) / motor->moi;
    motor->velocity += dOmege * dt;
}

Motor* create_motor(double emf_constant, double torque_constant, double moi, double friction) {
    Motor* motor = malloc(sizeof(struct Motor));
    motor->emf_constant = emf_constant;
    motor->torque_constant = torque_constant;
    motor->inductance = 0.001;
    motor->moi = moi;
    motor->friction = friction;
    motor->last_update = 0;
    motor->velocity = 0;
    motor->current = 0;
    motor->resistance = 10;
    motor->back_emf = 0;
    return motor;
}

int main(void) {
    Motor* motor = create_motor(0.25, 0.01, 0.00001, 0.000001);

    while (1)
    {
        const double physics_dt = 0.00005;
        clock_t time = clock();
        double dt = (double)(time - motor->last_update) / CLOCKS_PER_SEC;
        double accumulated_t = 0;

        while (accumulated_t < dt) {
            update_motor(motor, 5, physics_dt);
            accumulated_t += physics_dt;
        }

        motor->last_update = time;

        printf("Velocity: %.2f | Voltage: %.2f | Current: %.2f\n",
                        motor->velocity, motor->voltage, motor->current);

        sleep_ms(10);
    }

    free(motor);

    return 0;
}
