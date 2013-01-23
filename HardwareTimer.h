
#include <Arduino.h>

class SAM3X8E_HardwareTimer {

public:
	SAM3X8E_HardwareTimer(Tc *_tc, int _channel, int _id, IRQn_Type _irqn);

	void enable()  { pmc_enable_periph_clk(id); }
	void disable() { pmc_disable_periph_clk(id); }

	void enableInterrupt()  { NVIC_EnableIRQ(irqn); }
	void disableInterrupt() { NVIC_DisableIRQ(irqn); }

	void start() { CCR(TC_CCR_CLKEN | TC_CCR_SWTRG); }
	void stop()  { CCR(TC_CCR_CLKDIS); }

	void waveformMode() { CMR_WAVE(true); }
	void captureMode() { CMR_WAVE(false); }

	void onService() {
	}

	enum ExternalEvent { EVENT_PIN_B, EVENT_XC0, EVENT_XC1, EVENT_XC2 };

	void setExternalEvent(ExternalEvent v) {
		static const uint32_t modes[] = {
			TC_CMR_EEVT_TIOB, TC_CMR_EEVT_XC0,
			TC_CMR_EEVT_XC1, TC_CMR_EEVT_XC2
		};
		CMR_EEVT(modes[v]);
	}

	enum WaveformSelection { UP, UPDOWN, UP_RC, UPDOWN_RC };

	void setWaveform(WaveformSelection w) {
		static const uint32_t modes[] = {
			TC_CMR_WAVSEL_UP, TC_CMR_WAVSEL_UPDOWN,
			TC_CMR_WAVSEL_UP_RC, TC_CMR_WAVSEL_UPDOWN_RC
		};
		CMR_WAVSEL(modes[w]);
	}

	enum ClockMode { CLOCK1, CLOCK2, CLOCK3, CLOCK4, CLOCK5, XC0, XC1, XC2 };

	void setClock(ClockMode mode) {
		static const uint32_t modes[] = {
			TC_CMR_TCCLKS_TIMER_CLOCK1, TC_CMR_TCCLKS_TIMER_CLOCK2,
			TC_CMR_TCCLKS_TIMER_CLOCK3, TC_CMR_TCCLKS_TIMER_CLOCK4,
			TC_CMR_TCCLKS_TIMER_CLOCK5, TC_CMR_TCCLKS_XC0,
			TC_CMR_TCCLKS_XC1, TC_CMR_TCCLKS_XC2
		};
		CMR_TCCLKS(modes[mode]);
	}

	enum CompareEffect { NONE, CLEAR, SET, TOGGLE };

	void setRACompareEffectOnOutputA(CompareEffect v) {
		static const uint32_t modes[] = {
			TC_CMR_ACPA_NONE, TC_CMR_ACPA_CLEAR,
			TC_CMR_ACPA_SET, TC_CMR_ACPA_TOGGLE
		};
		CMR_ACPA(modes[v]);
	}
	void setRCCompareEffectOnOutputA(CompareEffect v) {
		static const uint32_t modes[] = {
			TC_CMR_ACPC_NONE, TC_CMR_ACPC_CLEAR,
			TC_CMR_ACPC_SET, TC_CMR_ACPC_TOGGLE
		};
		CMR_ACPC(modes[v]);
	}
	void setRBCompareEffectOnOutputB(CompareEffect v) {
		static const uint32_t modes[] = {
			TC_CMR_BCPB_NONE, TC_CMR_BCPB_CLEAR,
			TC_CMR_BCPB_SET, TC_CMR_BCPB_TOGGLE
		};
		CMR_BCPB(modes[v]);
	}
	void setRCCompareEffectOnOutputB(CompareEffect v) {
		static const uint32_t modes[] = {
			TC_CMR_BCPC_NONE, TC_CMR_BCPC_CLEAR,
			TC_CMR_BCPC_SET, TC_CMR_BCPC_TOGGLE
		};
		CMR_BCPC(modes[v]);
	}

#define REG(reg) \
	void reg(uint32_t v) { tcc->TC_##reg = v; }; \
	uint32_t reg()       { return tcc->TC_##reg; };
	// Example:
	// REG(RA) generates:
	//   void RA(uint32_t v) { tcc->TC_RA = v; };
	//   uint32_t RA()       { return tcc->TC_RA; };
	REG(RA);
	REG(RB);
	REG(RC);
	REG(CMR);
	REG(CCR);
	REG(CV);

#define REG_SUBFIELD(reg, sub) \
	void reg##_##sub(uint32_t v) { reg((reg() & ~TC_##reg##_##sub##_Msk) | v); };
	// Example:
	//   REG_SUBFIELD(CMR, ACPA) generates:
	//   void CMR_ACPA(uint32_t v) { CMR((CMR() & ~TC_CMR_ACPA_Msk) | v); }
#define REG_SUBBIT(reg, sub) \
	void reg##_##sub(bool v) { \
		if (v) reg(reg() | TC_##reg##_##sub); \
		else reg(reg() & ~TC_##reg##_##sub); \
	};
	// Example:
	//   REG_SUBBIT(CMR, WAVE) generates:
	// void CMR_##sub(bool v) { \
	//    if (v) CMR(CMR() | TC_CMR_WAVE); \
	//    else CMR(CMR() & ~TC_CMR_WAVE); \
	// };
	REG_SUBFIELD(CMR, ACPA)
	REG_SUBFIELD(CMR, ACPC)
	REG_SUBFIELD(CMR, BCPB)
	REG_SUBFIELD(CMR, BCPC)
	REG_SUBFIELD(CMR, TCCLKS)
	REG_SUBFIELD(CMR, WAVSEL)
	REG_SUBFIELD(CMR, EEVT)
	REG_SUBBIT(CMR, WAVE)

private:
	Tc *tc;
	TcChannel *tcc;
	IRQn_Type irqn;
	int channel;
	int id;
};

extern SAM3X8E_HardwareTimer Timer0;
extern SAM3X8E_HardwareTimer Timer1;
extern SAM3X8E_HardwareTimer Timer2;
extern SAM3X8E_HardwareTimer Timer3;
extern SAM3X8E_HardwareTimer Timer4;
extern SAM3X8E_HardwareTimer Timer5;
extern SAM3X8E_HardwareTimer Timer6;
extern SAM3X8E_HardwareTimer Timer7;
extern SAM3X8E_HardwareTimer Timer8;
