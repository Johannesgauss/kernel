unsafe extern "C" {
    #[link_name = "irqr_add"]
    pub fn irqr_add(irqr: i32, handler: extern "C" fn());
}
