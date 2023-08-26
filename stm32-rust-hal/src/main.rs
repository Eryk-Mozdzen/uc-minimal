#![no_std]
#![no_main]

use cortex_m_rt::{entry};
use stm32f4xx_hal::{delay::Delay, stm32, prelude::*};
#[allow(unused_imports)]
use panic_halt;

#[entry]
fn main() -> ! {
    let device = stm32::Peripherals::take().unwrap();
    let core = cortex_m::Peripherals::take().unwrap();

    let rcc = device.RCC.constrain();
    let clocks = rcc.cfgr.sysclk(100.mhz()).freeze();
    let mut delay = Delay::new(core.SYST, clocks);

    let gpioa = device.GPIOA.split();
    let mut led = gpioa.pa5.into_push_pull_output();

    loop {
        led.set_high().ok();
        delay.delay_ms(1000u16);

        led.set_low().ok();
        delay.delay_ms(1000u16);
    }
}
