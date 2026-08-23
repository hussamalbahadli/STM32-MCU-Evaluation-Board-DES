# My notes on RM0008 — STM32F103

> Rule: don't write a single driver line before filling in its section here.

## Register addresses (RM0008 — Memory map, Table 3)

| Peripheral | Base | Bus |
|---|---|---|
| TIM2 | `0x40000000` | APB1 |
| TIM3 | `0x40000400` | APB1 |
| TIM4 | `0x40000800` | APB1 |
| USART2 | `0x40004400` | APB1 |
| I2C1 | `0x40005400` | APB1 |
| AFIO | `0x40010000` | APB2 |
| EXTI | `0x40010400` | APB2 |
| GPIOA | `0x40010800` | APB2 |
| GPIOB | `0x40010C00` | APB2 |
| GPIOC | `0x40011000` | APB2 |
| GPIOD | `0x40011400` | APB2 |
| ADC1 | `0x40012400` | APB2 |
| TIM1 | `0x40012C00` | APB2 |
| SPI1 | `0x40013000` | APB2 |
| USART1 | `0x40013800` | APB2 |
| RCC | `0x40021000` | AHB |
| FLASH | `0x40022000` | AHB |
| SysTick | `0xE000E010` | **Core — no RCC** |
| NVIC | `0xE000E100` | **Core — no RCC** |

## RCC — Clock (§7)
- Every peripheral's clock is **gated off** at boot. A register with no clock reads zero and writes have no effect on it.
- `SW[1:0]` selects the source, and `SWS[3:2]` reports the actual source in use — **read SWS to confirm**.
- Above 48 MHz you must set `FLASH_ACR` latency = 2, otherwise an immediate HardFault.
- The PLL doesn't accept configuration changes while running — turn it off first.

## GPIO — (§9)
- Four bits per pin: `CNF[1:0]` + `MODE[1:0]`.
- `CRL` for pins 0–7 · `CRH` for pins 8–15 ← **the most common mistake**.
- `MODE`: `00` input · `01` 10MHz · `10` 2MHz · `11` 50MHz
- `CNF` in input mode: `00` analog · `01` floating · `10` pull-up/down (direction from `ODR`)
- `CNF` in output mode: `00` PP · `01` OD · `10` AF-PP · `11` AF-OD
- ⚠️ F4/F7/H7 family is completely different: `MODER`/`OTYPER`/`OSPEEDR`/`PUPDR`/`AFR`

## TIM — PWM Input Mode (§15.3.6)
- A single pin `TI1` feeds two capture channels: `IC1` on the rising edge and `IC2` on the falling edge.
- `SMS = 100` (Reset Mode) + `TS = 101` (TI1FP1) ⇒ every rising edge resets the counter.
- Result: `CCR1` = period · `CCR2` = pulse width.
- `PSC = (fCK / 1000000) - 1` makes each tick = 1 microsecond ⇒ reading is directly in microseconds.
- 🔴 **`URS` in `CR1` must be 1.** In Reset Mode every pulse resets the counter,
  and the reset raises `UIF` if `URS = 0` ⇒ the signal-loss detector fires 50 times/second.
- `IC1F`/`IC2F` = `0011` noise filter — necessary with an RC receiver.

## TODO
- [ ] SysTick — the 24-bit down-counter and `COUNTFLAG`
- [ ] NVIC — `AIRCR` requires `VECTKEY = 0x05FA` otherwise the write is ignored
- [ ] EXTI — `PR` is cleared **by writing 1**, not 0
- [ ] USART — computing `BRR` from mantissa/fraction
- [ ] SPI — CPOL/CPHA and their relation to sensors
- [ ] I2C — the state machine and ACK/NACK
- [ ] ADC — sample times and scan mode
- [ ] DMA — priorities and circular mode
