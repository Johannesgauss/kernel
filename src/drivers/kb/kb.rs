use crate::port::{inb, outb};

// C ADAPT INIT
unsafe extern "C" {
    #[link_name = "print_char"]
    fn c_print_char(char: u8);
    fn c_print_line(s: *const u8);
}
pub fn print_char(char: u8) { unsafe { c_print_char(char); }; }
// C ADAPT END
#[repr(C)]
pub struct idt_stack_call {
    _private: [u8; 176],
}
//pub fn print_line(char: u8) { unsafe { unsafe_c_print_line(char); }; }
// C ADAPT END



#[no_mangle]
pub extern "C" fn kb_handler()// -> Option<i8>
{
    let scancode = inb(0x60);

    let eqchar = match scancode {
        0x10 => Some(b'q'),
        0x11 => Some(b'w'),
        _ => None,
    };

    if let Some(c) = eqchar {
         print_char(c);
    }

    //return eqchar;
}
