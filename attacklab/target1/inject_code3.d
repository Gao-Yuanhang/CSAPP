
inject_code3.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <.text>:
   0:	68 fa 18 40 00       	pushq  $0x4018fa
   5:	48 bf 35 39 62 39 39 	movabs $0x6166373939623935,%rdi
   c:	37 66 61 
   f:	48 89 7c 24 28       	mov    %rdi,0x28(%rsp)
  14:	48 c7 44 24 30 00 00 	movq   $0x0,0x30(%rsp)
  1b:	00 00 
  1d:	48 8d 7c 24 28       	lea    0x28(%rsp),%rdi
  22:	c3                   	retq   
