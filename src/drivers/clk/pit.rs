use crate::port::{inb, outb};

// C ADAPT INIT
unsafe extern "C" {
    #[link_name = "irqr_add"]
    fn c_irqr_add(irqr:i32, handler: extern "C" fn());
}
fn irqr_add(irqr:i32, handler:extern "C" fn()) { unsafe { c_irqr_add(irqr, handler); }}
// C ADAPT END

const PIT_COMMAND_REG: u16 = 0x43;
const PIT_DATA_CHANNEL0:u16 = 0x40;

#[no_mangle]
pub extern "C" fn timer_phase(hz: i32)
{
    let divisor:u16 = (1193180 / hz) as u16;
    outb(PIT_COMMAND_REG, 0b00110000 | 0b00000110);
    outb(PIT_DATA_CHANNEL0, (divisor & 0xFF) as u8);
    outb(PIT_DATA_CHANNEL0, (divisor >> 8) as u8);
}


use core::sync::atomic::{AtomicUsize, Ordering};

static TIMER_TICKS:AtomicUsize = AtomicUsize::new(0);

#[no_mangle]
pub extern "C" fn timer_handler()
{
    TIMER_TICKS.fetch_add(1, Ordering::Relaxed);
}

#[no_mangle]
pub extern "C" fn timer_add() -> bool
{
    timer_phase(100);
    irqr_add(0, timer_handler);

    return true;
}
