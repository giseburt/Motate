/*
  KL05ZTimers.cpp - Library for the Arduino-compatible Motate system
  http://github.com/synthetos/motate/

  Copyright (c) 2013 Robert Giseburt

	This file is part of the Motate Library.

	This file ("the software") is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License, version 2 as published by the
	Free Software Foundation. You should have received a copy of the GNU General Public
	License, version 2 along with the software. If not, see <http://www.gnu.org/licenses/>.

	As a special exception, you may use this file as part of a software library without
	restriction. Specifically, if other files instantiate templates or use macros or
	inline functions from this file, or you compile this file and link it with  other
	files to produce an executable, this file does not by itself cause the resulting
	executable to be covered by the GNU General Public License. This exception does not
	however invalidate any other reasons why the executable file might be covered by the
	GNU General Public License.

	THE SOFTWARE IS DISTRIBUTED IN THE HOPE THAT IT WILL BE USEFUL, BUT WITHOUT ANY
	WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
	OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT
	SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
	OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


#if defined(__KL05Z__)

#include "Freescale_klxx/KL05ZTimers.h"
//#include "Reset.h"

namespace Motate {
	/* System-wide tick counter */
	/*  Inspired by code from Atmel and Arduino.
	 *  Some of which is:   Copyright (c) 2012 Arduino. All right reserved.
	 *  Some of which is:   Copyright (c) 2011-2012, Atmel Corporation. All rights reserved.
	 */

	Timer<SysTickTimerNum> SysTickTimer;
	Timer<WatchDogTimerNum> WatchDogTimer;

	volatile uint32_t Timer<SysTickTimerNum>::_motateTickCount = 0;

} // namespace Motate

extern "C" void SysTick_Handler(void)
{
//	if (sysTickHook)
//		sysTickHook();

//	tickReset();

	Motate::SysTickTimer._increment();

	if (Motate::SysTickTimer.interrupt) {
		Motate::SysTickTimer.interrupt();
	}
}

extern "C" {

    void TPM0_IRQHandler(void) { Motate::Timer<0>::interrupt(); }
    void TPM1_IRQHandler(void) { Motate::Timer<1>::interrupt(); }

}

#endif // __KL05Z__
