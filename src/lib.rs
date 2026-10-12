#![no_std]
#![no_main]

use core::panic::PanicInfo;

#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    loop {
        core::hint::spin_loop();
    }
}

pub mod ffi;
pub mod drivers;

#[path = "util/panic.rs"]
pub mod panic;

pub use drivers::port;
