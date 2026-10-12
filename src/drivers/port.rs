#[no_mangle]
#[inline(always)]
pub extern "C" fn inb(port: u16) -> u8
{
    let value:u8;
    unsafe {
        core::arch::asm!(
            "in al, dx",
            in("dx") port,
            out("al") value,
            options(nomem, nostack, preserves_flags)
        );
    };
    return value;
}


#[no_mangle]
#[inline(always)]
pub extern "C" fn outb(port: u16, value: u8) -> u8
{
    unsafe {
        core::arch::asm!(
            "out dx, al",
            in("dx") port,
            in("al") value,
            options(nomem, nostack, preserves_flags)
        );
    };
    return value;
}

#[no_mangle]
pub extern "C" fn io_wait()
{
    outb(0x80, 0);
}
