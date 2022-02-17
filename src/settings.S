.data
.global enable_interrupts

.text

enable_interrupts:
	ei

	jr $ra
	nop
