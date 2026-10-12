use crate::ffi::gfx::print_line;

#[no_mangle]
extern "C" fn panic(msg: *const u8) -> !
{
    print_line(b"-- KERNEL PANIC! --\n\0".as_ptr());
    print_line(msg);

    unsafe {
        core::arch::asm!("cli");
        loop {
            core::arch::asm!("hlt");
        }
    }
}
