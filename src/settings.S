.data
.global enable_interrupts
.global delay

.text

enable_interrupts:
	ei

	jr $ra
	nop

delay:
    move $t0, $a0 #Save the input in ms from $a0 to $t0
    
    while:
        slt $t1, $0, $t0 #Check if 0 is smaller than $t0
        bne $t1, 1, end #If $t1 != 1 go to end
        nop
    
        addi $t0, $t0, -1 #Remove one ms from $t0

        li $t2, 0 #Set $t2 to 0
        li $t3, 3400 #Set t3 to 3400
        
        for:
            slt $t4, $t2, $t3 #Check if $t2 is less than $t3
            bne $t4, 1, forEnd #If $t3 != 1 go to end
            nop
        
            addi $t2, $t2, 1 #Add 1 to $t1
            j for
            nop

        forEnd:
        j while #Go back to the start of the while loop
        nop

    end:
    jr $ra
    nop
