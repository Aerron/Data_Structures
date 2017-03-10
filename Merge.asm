	.data
eol:	.asciiz	"\n"
	prompt1: .asciiz "Enter the number n  :- "
	prompt2: .asciiz "Enter the number A0 :-"
	prompt3: .asciiz "Enter the number d  :-"
	prompt4: .asciiz "Enter four different random numbers :"
	Array:   .word 400
	.text
	.globl main
main:	
		#$s5 for n 
		#prompt user to input number n
		li $v0,4
		la $a0,prompt1
		syscall 
		li $v0,5
		syscall 
		add $s5,$v0,$0
	
		#$s6 for A0
		#prompt user to input number A0
		li $v0,4
		la $a0,prompt2
		syscall 
		li $v0,5
		syscall 
		add $s6,$v0,$0
	
		#$s7 for d
		#prompt user to input number d
		li $v0,4
		la $a0,prompt3
		syscall 
		li $v0,5
		syscall 
		add $s7,$v0,$0
	

		#To generate the integers
		addi $t0,$0,1
		addi $t1,$0,0
		add $t2,$0,$s6
		sw  $s6,Array($t1)

	generate:	
		beq $t0,$s5,Exit1
		mul $t1,$t0,4
		add $t2,$t2,$s7
		sw  $t2,Array($t1)
		addi $t0,$t0,1
		j generate
	Exit1:

	la	$a0, Array	
	add $t0,$s5,$0		
	mul	$t0, $t0, 4		
	add	$a1, $a0, $t0	
	jal	mergesort		
	
		addi $t0,$0,0
	while12 :
		bge $t0,$s5,Exit12
		mul $t1,$t0,4
		lw  $s3,Array($t1)
		li  $v0,1
		add $a0,$0,$s3
		syscall
		li $v0,11
		li $a0,32
		syscall
		addi $t0,$t0,1
		j while12
	Exit12:
	li $v0,4
	la $a0,prompt4
	syscall
	li $v0,5
	syscall 
	add $t6,$v0,$0
	li $v0,5
	syscall 
	add $t7,$v0,$0
	li $v0,5
	syscall 
	add $t8,$v0,$0
	li $v0,5
	syscall 
	add $t9,$v0,$0
	addi $t0,$0,0
while1 :
	bge $t0,$s0,Exit5
	add $t5,$0,$t6
	sll $t4,$t5,11
	xor $t5,$t4,$t5
	srl $t4,$t5,8
	xor $t5,$t4,$t5
	add $t6,$0,$t7
	add $t7,$0,$t8
	add $t8,$0,$t9
	srl $t4,$t9,19
	xor $t9,$t9,$t4
	xor $t9,$t9,$t5
	mul $t1,$t0,4
	bgt $t9,$0,la
	sub $t9,$0,$t9
la:
	sw  $t9,Array($t1)
	addi $t0,$t0,1
	j while1
Exit5:
	la	$a0, Array	
	add $t0,$s5,$0		
	sll	$t0, $t0, 2	
	add	$a1, $a0, $t0
jal mergesort
addi $t0,$0,0
	while123:
		bge $t0,$s5,Exit123
		mul $t1,$t0,4
		lw  $s3,Array($t1)
		li  $v0,1
		add $a0,$0,$s3
		syscall
		li $v0,11
		li $a0,32
		syscall
		addi $t0,$t0,1
		j while123
	Exit123:
	#end main
	li	$v0,10
	syscall
	

mergesort:

	addi $sp, $sp, -16		
	sw	$ra, 0($sp)		
	sw	$a0, 4($sp)		
	sw	$a1, 8($sp)		
	
	sub $t0, $a1, $a0		
	ble	$t0, 4, mergesortsingle	
	
	srl	$t0, $t0, 3
	sll $t0,$t0,2		
	add	$a1, $a0, $t0	
	sw	$a1, 12($sp)
	
	lw 	$a1, 12($sp)
	lw  $a0, 4($sp)
	jal	mergesort		
	
	lw	$a0, 12($sp)	
	lw	$a1, 8($sp)		
	jal	mergesort		
	
	lw	$a0, 4($sp)		
	lw	$a1, 12($sp)	
	lw	$a2, 8($sp)		
	jal	merge			
mergesortsingle:				

	lw	 $ra, 0($sp)		
	addi $sp, $sp, 16
	jr	 $ra
		
			
	
merge:
	addi $sp, $sp, -16		
	sw   $ra, 0($sp)		
	sw   $a0, 4($sp)		
	sw   $a1, 8($sp)		
	sw   $a2, 12($sp)	
	
	move	$s0, $a0	
	move	$s1, $a1		
	
mergearr:

	lw	$t0, 0($s0)		
	lw	$t1, 0($s1)		
	
	bgt	$t1, $t0, ar	
	
	move	$a0, $s1	
	move	$a1, $s0	
	jal	inse			
	
	addi	$s1, $s1, 4	
ar:
	addi	$s0, $s0, 4	
	
	lw	$a2, 12($sp)	
	bge	$s0, $a2, mend	
	bge	$s1, $a2, mend	
	j	mergearr
	
mend:
	
	lw	$ra, 0($sp)		
	addi	$sp, $sp, 16
	jr 	$ra			
inse:
	add	$t0, $s5,$0
	ble	$a0, $a1, inse_end	
	addi	$t6, $a0, -4	
	lw	$t7, 0($a0)		
	lw	$t8, 0($t6)		
	sw	$t7, 0($t6)		
	sw	$t8, 0($a0)		
	move	$a0, $t6	
	j 	inse			
inse_end:
	jr	$ra			
	
