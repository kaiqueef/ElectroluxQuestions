//  * Created: 16/05/2022 21:00:00
//  *  Author: Kaique Ferreira
//  */
/**
 *  QUESTION 1: Imagine a situation where you have a circuit able to activate and deactivate a purely resistive load
    with a microcontroller. It is required to control the load power over time depending on the situation
    and the power cannot be instantly changed from 0% to 100%. Explain in simple words a method
    to achieve such effect, looking at both hardware and firmware aspects of the system. If an
    inductive load is used instead of a resistive load, can the same triggering method be used or do
    special precautions need to be taken?
 */

/**
 *  R: It needs a voltage regulated power circuit based on a PWM wave given by the microcontroller.
    the firmware must garantee that an PWM signal changes from 0% to 100% in the pace needed by the circuit when powering on and off (once it was said that cannot be instantly changed to 100%)
    If it is an purely inductive load, the power circuit must garantee that the current flow do not stop instantaneously, otherwise voltage will rise ( V = L(di/dt) ) and probably the circuit will be damaged. 
    Thus, the circuit must have a path to the current to flow and decay when it is needed to power off.
 */ 