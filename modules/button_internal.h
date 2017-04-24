/*
* Copyright (c) 2012, Alexander I. Mykyta
* All rights reserved.
* Supported and funded in part by RIT / NTID Center on Access Technology
* 
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met: 
* 
* 1. Redistributions of source code must retain the above copyright notice, this
*    list of conditions and the following disclaimer. 
* 2. Redistributions in binary form must reproduce the above copyright notice,
*    this list of conditions and the following disclaimer in the documentation
*    and/or other materials provided with the distribution. 
* 
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/**
* \addtogroup MOD_BUTTON
* \{
**/

/**
* \file
* \brief Internal include for \ref MOD_BUTTON "Pushbutton Events".
*    Abstracts register names between MSP430 devices
* \author Alex Mykyta 
* \date 7/22/2011
**/

///\}

#ifndef BUTTON_INTERNAL_H
#define BUTTON_INTERNAL_H

#include <msp430_xc.h>
#include <stdint.h>






// Potential future support:
// __MSP430_HAS_TB3__
// __MSP430_HAS_TB7__
// __MSP430_HAS_T0B3__
// __MSP430_HAS_T0B7__
// __MSP430_HAS_T1B3__
// __MSP430_HAS_T2B3__



//==================================================================================================
// Device Abstraction
//==================================================================================================
#if BUTTON_USE_DEV == 0
    #if (defined(__MSP430_HAS_TA3__ ) || \
         defined(__MSP430_HAS_TA5__ ) || \
         defined(__MSP430_HAS_T0A3__) || \
         defined(__MSP430_HAS_T0A5__))
    
        #define BUT_TCTL    TA0CTL
        #define BUT_TCCTL0    TA0CCTL0
        #define BUT_TCCTL1    TA0CCTL1
        #define BUT_TCCTL2    TA0CCTL2
        #define BUT_TR        TA0R
        #define BUT_TCCR0    TA0CCR0
        #define BUT_TCCR1    TA0CCR1
        #define BUT_TCCR2    TA0CCR2
        #define BUT_TIV        TA0IV
        #if defined(TA0EX0)
            #define BUT_TEX0    TA0EX0
        #endif
        
        #define BUT_TIMER_ISR_VECTOR    TIMER0_A1_VECTOR
    #else
        #error "Invalid BUTTON_USE_DEV in button_config.h"
    #endif
//--------------------------------------------------------------------------------------------------
#elif BUTTON_USE_DEV == 1
    #if (defined(__MSP430_HAS_T1A3__) || \
         defined(__MSP430_HAS_T1A5__))
    
        #define BUT_TCTL    TA1CTL
        #define BUT_TCCTL0    TA1CCTL0
        #define BUT_TCCTL1    TA1CCTL1
        #define BUT_TCCTL2    TA1CCTL2
        #define BUT_TR        TA1R
        #define BUT_TCCR0    TA1CCR0
        #define BUT_TCCR1    TA1CCR1
        #define BUT_TCCR2    TA1CCR2
        #define BUT_TIV        TA1IV
        #if defined(TA1EX0)
            #define BUT_TEX0    TA1EX0
        #endif
        
        #define BUT_TIMER_ISR_VECTOR    TIMER1_A1_VECTOR
    
    #else
        #error "Invalid BUTTON_USE_DEV in button_config.h"
    #endif
//--------------------------------------------------------------------------------------------------
#elif BUTTON_USE_DEV == 2
    #if (defined(__MSP430_HAS_T2A3__))
    
        #define BUT_TCTL    TA2CTL
        #define BUT_TCCTL0    TA2CCTL0
        #define BUT_TCCTL1    TA2CCTL1
        #define BUT_TCCTL2    TA2CCTL2
        #define BUT_TR        TA2R
        #define BUT_TCCR0    TA2CCR0
        #define BUT_TCCR1    TA2CCR1
        #define BUT_TCCR2    TA2CCR2
        #define BUT_TIV        TA2IV
        #if defined(TA2EX0)
            #define BUT_TEX0    TA1EX0
        #endif
        
        #define BUT_TIMER_ISR_VECTOR    TIMER2_A1_VECTOR
    
    #else
        #error "Invalid BUTTON_USE_DEV in button_config.h"
    #endif
//--------------------------------------------------------------------------------------------------
#else
    #error "Invalid BUTTON_USE_DEV in button_config.h"
#endif


//==================================================================================================
// Clock Setup
//==================================================================================================

#if BUTTON_CLK_SRC == 1
    // ACLK
    #define BUT_FCLK    ACLK_FREQ
#elif BUTTON_CLK_SRC == 2
    // SMCLK
    #define BUT_FCLK    SMCLK_FREQ
#else
    #error "Invalid BUTTON_CLK_SRC in button_config.h"
#endif

#if defined(BUT_TEX0)
    #define BUT_FCLKDIV        (BUT_FCLK/((1<<BUTTON_IDIV)*(BUTTON_IDIVEX+1)))
#else
    #define BUT_FCLKDIV        (BUT_FCLK/(1<<BUTTON_IDIV))
#endif

#define BUTTON_DEBOUNCETICKS    ((BUT_FCLKDIV*BUTTON_DEBOUNCETIME)/1000)
#define BUTTON_HOLDTICKS        ((BUT_FCLKDIV*BUTTON_HOLDTIME)/1000)

#if (BUTTON_DEBOUNCETICKS < 2)
    #error "Resulting timer clock frequency is too slow to achieve the debounce time"
#endif

#if (BUTTON_HOLDTICKS > 65535)
    #error "Resulting timer clock frequency is too high to achieve the hold time"
#endif

//==================================================================================================
// Declarations
//==================================================================================================

typedef struct{
    uint8_t en;
    uint8_t inverted;
    uint8_t hit_down;
    uint8_t hit_up;
    uint8_t pending_hold;
}BUTTON_t;


//--------------------------------------------------------------------------------------------------
#endif /*_BUTTON_INTERNAL_H_*/
