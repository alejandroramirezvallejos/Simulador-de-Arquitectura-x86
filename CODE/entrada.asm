pushq %rbp
movq %rsp, %rbp
subq $48, %rsp
movl $1, -4(%rbp)
movl -4(%rbp), %eax
addl $1, %eax
movl %eax, -8(%rbp)
movl $0, %eax

