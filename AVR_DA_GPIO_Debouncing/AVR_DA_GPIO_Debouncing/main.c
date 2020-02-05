/**
 * \file main.c
 *
 * \brief Main source file.
 *
 (c) 2019 Microchip Technology Inc. and its subsidiaries.
    Subject to your compliance with these terms, you may use this software and
    any derivatives exclusively with Microchip products. It is your responsibility
    to comply with third party license terms applicable to your use of third party
    software (including open source software) that may accompany Microchip software.
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE.
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#define TOP_VALUE 0xFFFF

static void PORT_init(void);
static void EVSYS_init(void);
static void TIMER_0_init(void);
static void SYSTEM_init(void);
static void BUTTON_releaseCallback(void);
static void BUTTON_pressCallback(void);

static void PORT_init(void)
{
    PORTC.DIR |= PIN6_bm;
    PORTC.OUT |= PIN6_bm;

    PORTC.DIR &= ~(PIN7_bm);
    PORTC.PIN7CTRL |= PORT_PULLUPEN_bm;
}

static void EVSYS_init(void)
{
    EVSYS.CHANNEL3 = EVSYS_CHANNEL3_PORTC_PIN7_gc;
    EVSYS.USERTCB0CAPT = EVSYS_USER_CHANNEL3_gc;
}

static void TIMER_0_init(void)
{
    TCB0.CCMP = TOP_VALUE;
    TCB0.CTRLB = TCB_CNTMODE_SINGLE_gc;
    TCB0.EVCTRL = TCB_CAPTEI_bm | TCB_EDGE_bm;
    TCB0.CTRLA = TCB_CLKSEL0_bm | TCB_ENABLE_bm;
    TCB0.CNT = TOP_VALUE;
    TCB0.INTCTRL = TCB_CAPT_bm;
}

static void SYSTEM_init(void)
{
    PORT_init();
    EVSYS_init();
    TIMER_0_init();

    sei();
}

static void BUTTON_releaseCallback(void)
{
    PORTC.OUTSET |= PIN6_bm;
}

static void BUTTON_pressCallback(void)
{
    PORTC.OUTCLR |= PIN6_bm;
}

ISR(TCB0_INT_vect)
{
    if (PORTC.IN & PIN7_bm)
    {
        BUTTON_releaseCallback();
    }
    else
    {
        BUTTON_pressCallback();
    }

    TCB0.INTFLAGS = TCB_CAPT_bm;
}

int main(void)
{
    SYSTEM_init();

    while (1)
    {
        ;
    }
}