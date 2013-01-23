
#include <HardwareTimer.h>

SAM3X8E_HardwareTimer::SAM3X8E_HardwareTimer(Tc *_tc, int _channel, int _id, IRQn_Type _irqn) :
	tc(_tc), channel(_channel), tcc(tc->TC_CHANNEL+_channel),
	id(_id), irqn(_irqn)
{
	// Empty
}

SAM3X8E_HardwareTimer Timer0(TC0, 0, ID_TC0, TC0_IRQn);
SAM3X8E_HardwareTimer Timer1(TC0, 1, ID_TC1, TC1_IRQn);
SAM3X8E_HardwareTimer Timer2(TC0, 2, ID_TC2, TC2_IRQn);
SAM3X8E_HardwareTimer Timer3(TC1, 0, ID_TC3, TC3_IRQn);
SAM3X8E_HardwareTimer Timer4(TC1, 1, ID_TC4, TC4_IRQn);
SAM3X8E_HardwareTimer Timer5(TC1, 2, ID_TC5, TC5_IRQn);
SAM3X8E_HardwareTimer Timer6(TC2, 0, ID_TC6, TC6_IRQn);
SAM3X8E_HardwareTimer Timer7(TC2, 1, ID_TC7, TC7_IRQn);
SAM3X8E_HardwareTimer Timer8(TC2, 2, ID_TC8, TC8_IRQn);

void TC3_Handler() { Timer3.onService(); }
