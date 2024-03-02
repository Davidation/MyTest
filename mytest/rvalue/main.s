	.file	"main.cpp"
	.text
	.section	.rodata
	.type	_ZStL19piecewise_construct, @object
	.size	_ZStL19piecewise_construct, 1
_ZStL19piecewise_construct:
	.zero	1
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
.LC0:
	.string	"A Construct"
	.section	.text._ZN1AC2Ev,"axG",@progbits,_ZN1AC5Ev,comdat
	.align 2
	.weak	_ZN1AC2Ev
	.type	_ZN1AC2Ev, @function
_ZN1AC2Ev:
.LFB1937:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	$0, (%rax)
	movl	$.LC0, %esi
	movl	$_ZSt4cout, %edi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, %esi
	movq	%rdx, %rdi
	call	_ZNSolsEi
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	movq	%rax, %rdi
	call	_ZNSolsEPFRSoS_E
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1937:
	.size	_ZN1AC2Ev, .-_ZN1AC2Ev
	.weak	_ZN1AC1Ev
	.set	_ZN1AC1Ev,_ZN1AC2Ev
	.section	.rodata
.LC1:
	.string	"A Destruct"
	.section	.text._ZN1AD2Ev,"axG",@progbits,_ZN1AD5Ev,comdat
	.align 2
	.weak	_ZN1AD2Ev
	.type	_ZN1AD2Ev, @function
_ZN1AD2Ev:
.LFB1940:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA1940
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	$.LC1, %esi
	movl	$_ZSt4cout, %edi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, %esi
	movq	%rdx, %rdi
	call	_ZNSolsEi
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	movq	%rax, %rdi
	call	_ZNSolsEPFRSoS_E
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1940:
	.globl	__gxx_personality_v0
	.section	.gcc_except_table._ZN1AD2Ev,"aG",@progbits,_ZN1AD5Ev,comdat
.LLSDA1940:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE1940-.LLSDACSB1940
.LLSDACSB1940:
.LLSDACSE1940:
	.section	.text._ZN1AD2Ev,"axG",@progbits,_ZN1AD5Ev,comdat
	.size	_ZN1AD2Ev, .-_ZN1AD2Ev
	.weak	_ZN1AD1Ev
	.set	_ZN1AD1Ev,_ZN1AD2Ev
	.text
	.globl	_Z4GetAv
	.type	_Z4GetAv, @function
_Z4GetAv:
.LFB1942:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN1AC1Ev
	nop
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1942:
	.size	_Z4GetAv, .-_Z4GetAv
	.globl	_Z7GetARefv
	.type	_Z7GetARefv, @function
_Z7GetARefv:
.LFB1943:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 3, -24
	leaq	-20(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN1AC1Ev
	movl	$0, %ebx
	leaq	-20(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN1AD1Ev
	movq	%rbx, %rax
	addq	$24, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1943:
	.size	_Z7GetARefv, .-_Z7GetARefv
	.globl	main
	.type	main, @function
main:
.LFB1944:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA1944
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 3, -24
	leaq	-28(%rbp), %rax
	movq	%rax, %rdi
.LEHB0:
	call	_Z4GetAv
.LEHE0:
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
.LEHB1:
	call	_Z4GetAv
.LEHE1:
	leaq	-32(%rbp), %rax
	movq	%rax, -24(%rbp)
	movl	$0, %ebx
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN1AD1Ev
	leaq	-28(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN1AD1Ev
	movl	%ebx, %eax
	jmp	.L11
.L10:
	movq	%rax, %rbx
	leaq	-28(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN1AD1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB2:
	call	_Unwind_Resume
.LEHE2:
.L11:
	addq	$24, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1944:
	.section	.gcc_except_table,"a",@progbits
.LLSDA1944:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE1944-.LLSDACSB1944
.LLSDACSB1944:
	.uleb128 .LEHB0-.LFB1944
	.uleb128 .LEHE0-.LEHB0
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB1-.LFB1944
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L10-.LFB1944
	.uleb128 0
	.uleb128 .LEHB2-.LFB1944
	.uleb128 .LEHE2-.LEHB2
	.uleb128 0
	.uleb128 0
.LLSDACSE1944:
	.text
	.size	main, .-main
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB2433:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	cmpl	$1, -4(%rbp)
	jne	.L14
	cmpl	$65535, -8(%rbp)
	jne	.L14
	movl	$_ZStL8__ioinit, %edi
	call	_ZNSt8ios_base4InitC1Ev
	movl	$__dso_handle, %edx
	movl	$_ZStL8__ioinit, %esi
	movl	$_ZNSt8ios_base4InitD1Ev, %edi
	call	__cxa_atexit
.L14:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2433:
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.type	_GLOBAL__sub_I__Z4GetAv, @function
_GLOBAL__sub_I__Z4GetAv:
.LFB2434:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$65535, %esi
	movl	$1, %edi
	call	_Z41__static_initialization_and_destruction_0ii
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2434:
	.size	_GLOBAL__sub_I__Z4GetAv, .-_GLOBAL__sub_I__Z4GetAv
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I__Z4GetAv
	.hidden	__dso_handle
	.ident	"GCC: (GNU) 8.5.0 20210514 (TencentOS 8.5.0-18)"
	.section	.note.GNU-stack,"",@progbits
