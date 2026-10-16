void *irq_routines[16] = {
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0
};

void irqr_add(int irqr, void (*handler)(void))
{
	irq_routines[irqr] = handler;
}
