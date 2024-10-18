
if(${BUILD_TARGET} MATCHES "EMULATOR")
    SET(EEAR "(&variable1)")
    SET(EEDR "(&variable1)")
    SET(EECR "(&variable1)")

elseif(${BUILD_TARGET} MATCHES "MCU")
    SET(EEAR    "((uint16_t*)0x41)")
    SET(EEDR    "((uint8_t*)0x40)")
    SET(EECR    "((uint8_t*)0x3F)")
    SET(TIMER0  "(timer_registers*)(0x44)")
    SET(TIMER2  "(timer_registers*)(0xB0)")
    SET(TIFR0   "(uint8_t*)(0x35)")
    SET(TIFR1   "(uint8_t*)(0x36)")
    SET(TIFR2   "(uint8_t*)(0x37)")
    SET(PORTB   "(gpio*)(0x23)")
    SET(PORTC   "(gpio*)(0x26)")
    SET(PORTD   "(gpio*)(0x29)")
    SET(ADMUX   "((uint8_t*)0x7C)")

endif()

configure_file(registers.h.in "${CMAKE_SOURCE_DIR}/src/lib/memory/registers.h")
