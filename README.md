# STM32-MCU-Evaluation-Board-DES

Drivers and examples for **STM32F103** written from scratch directly on the registers ―
no ST HAL and no CubeMX-generated code.

Goal: **understand every bit we write**, then use it for teaching and projects.

> The matching version on AVR: [AVR-MCU-Evaluation-Board-DES](https://github.com/hussamalbahadli/AVR-MCU-Evaluation-Board-DES)
> The exact same architecture ― only the register names change.

---

## Architecture

Every driver has exactly four files, no more and no less:

| File | Content | Who reads it |
|---|---|---|
| `X_interface.h` | Public signatures and constants ― **the contract** | The user |
| `X_private.h` | Register addresses and bit numbers | The driver only |
| `X_config.h` | Everything that is configurable | The user, before building |
| `X_program.c` | The implementation | No one, once it's written |

**Golden rule:** if we port the code to another chip, only `_private.h` and `_program.c` change.
`_interface.h` doesn't change a single character ― which is why the application layer never changes.

```
Driver/
├── LIB/          STD_TYPES.h · BIT_MATH.h
├── MCAL/         What touches the registers directly
│   ├── RCC/      ✅  Clock ― before everything else
│   ├── GPIO/     ✅  Digital input and output
│   └── ICU/      ✅  Hardware pulse-width measurement
└── HAL/          What never touches registers at all
    └── PWM2LOGIC/ ✅  PWM to logic-level conversion

Example/
├── 01_GPIO_Blink/     ✅
└── 02_PWM_To_Logic/   ✅

Docs/
└── RM0008_notes.md
```

---

## Driver status

| # | Driver | Layer | Status | Tested on hardware |
|---|---|---|---|---|
| 1 | `RCC` | MCAL | ✅ | ✅ |
| 2 | `GPIO` | MCAL | ✅ | ✅ |
| 3 | `ICU` | MCAL | ✅ | ✅ |
| 4 | `PWM2LOGIC` | HAL | ✅ | ✅ |
| 5 | `STK` (SysTick) | MCAL | ⬜ | — |
| 6 | `NVIC` | MCAL | ⬜ | — |
| 7 | `AFIO` + `EXTI` | MCAL | ⬜ | — |
| 8 | `USART` | MCAL | ⬜ | — |
| 9 | `SPI` | MCAL | ⬜ | — |
| 10 | `I2C` | MCAL | ⬜ | — |
| 11 | `ADC` | MCAL | ⬜ | — |
| 12 | `TIM` (PWM out) | MCAL | ⬜ | — |
| 13 | `DMA` | MCAL | ⬜ | — |

The HAL layer (`CLCD` · `KPD` · `SSD` · `SW` · `DC_MOTOR` · `STEPPER` · `LM35` · `EEPROM`)
is ported from the AVR repo by replacing `DIO_*` with `GPIO_*` ― since it never touches registers anyway.

---

## Chip and tools

- **MCU:** STM32F103RBT6 (also works on STM32F103C8 "Blue Pill" with a `GPIO_config.h` tweak)
- **IDE:** Keil MDK-ARM
- **Programmer:** ST-Link V2
- **The only reference used:** ST's `RM0008` ― no videos, no articles

### Include paths required in Keil

```
Driver/LIB
Driver/MCAL/RCC
Driver/MCAL/GPIO
Driver/MCAL/ICU
Driver/HAL/PWM2LOGIC
```

---

## How to add a new driver

1. Read the peripheral chapter in `RM0008` and log your notes in `Docs/RM0008_notes.md`.
2. Draw its register map by hand.
3. Write `_private.h` ― addresses and bit numbers only.
4. Write `_interface.h` ― **signatures before any implementation**.
5. Write `_config.h` ― every option with a comment listing its allowed values.
6. Write `_program.c`.
7. Build an example in `Example/NN_<name>/` ― the smallest program that proves it works.
8. Test it on hardware, then open **System Viewer** and confirm the register values are what you expected.
9. `git commit` with a message explaining **what** and **why**.

---

## Coding style

- Register definition follows the same style as AVR: `*((volatile u32*)(BASE + OFFSET))`
- Parameter names: `Copy_u8...` · local variables: `Local_u8...`
- Functions: `MODULE_voidName` · `MODULE_u8Name` depending on the return type
- **No** `typedef struct` for registers, **no** complex macros, **no** `ErrorStatus` in this version
  ― these are all later lessons added once the student masters the basics

## License

For educational and personal use.
GNU GENERAL PUBLIC LICENSE
