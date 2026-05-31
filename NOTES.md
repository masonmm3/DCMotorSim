
# Basic Intro
---
Motors are a core part of robotics in todays world. They are highly controllable and provide a consistent method of control. Thus, understanding them becomes all the more important.

Someone experienced with motors that doesn't understand their properties would tell you that RPM is controlled by Voltage, and Torque by Current. This is technically correct however it fails to understand certain behaviors.

# Basic Modeling
---
DC motors are relatively easy to model. They are made up of a resistive component, (voltage drop), an inductor (current load), and a dependent Voltage source (back emf)

![](Pasted%20image%2020260531143529.png)

# Mathematical model
---
Because we are able to draw the motor as a circuit that represent it we are able to solve for values such as RPM and Angular Position.

Solving the equations we can get the following governing differential equation which can be used to find important values.
> $$LJ \frac{d^2\omega}{dt^2} + (Lb + RJ) \frac{d\omega}{dt} + (K_t K_e + Rb)\omega = K_t V_{in}$$

which can be used to create a transfer function similar to the following for determining the velocity.
![](Pasted%20image%2020260531144733.png)

### Theoretical Behavior
---
Because $V_a$ relates proportionally to the motor velocity, we are able to understand why motors have a max speed. As the rpm increases the voltage at the dependent source increases, which decreases the voltage at the armature. This creates a meeting point where the current is no longer sufficient to accelerate and the back emf is increased to the point $V_a$ can not increase without a larger $V_{in}$ term. 

### Sources
---
https://www.scribd.com/document/858856371/Mathematical-Modelling-of-a-PMDC-Motor
