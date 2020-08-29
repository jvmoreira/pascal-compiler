
# *****************************************************************
# INICIO macros
# *****************************************************************


# -----------------------------------------------------------------
#  INPP
# -----------------------------------------------------------------

.macro INPP
   movl %esp, %eax
   movl $0, %edi
   movl %eax, D(,%edi,4)
.endm

# -----------------------------------------------------------------
#  PARA
# -----------------------------------------------------------------

.macro PARA
   movl $FIM_PGMA, %eax
   int  $SYSCALL
.endm

# -----------------------------------------------------------------
#  AMEM
# -----------------------------------------------------------------

.macro AMEM mem
   movl $\mem, %eax
   movl $4, %ebx
   imull %ebx, %eax
   subl %eax, %esp
.endm

# -----------------------------------------------------------------
#  DMEM
# -----------------------------------------------------------------

.macro DMEM mem
   movl $\mem, %eax
   movl $4, %ebx
   imull %ebx, %eax
   addl %eax, %esp
.endm


# -----------------------------------------------------------------
#  CRCT
# -----------------------------------------------------------------

.macro CRCT k
   pushl $\k
.endm



# -----------------------------------------------------------------
#  CRVL
# -----------------------------------------------------------------

.macro CRVL m n
   movl $\m, %edi
   movl D(,%edi,4), %eax
   movl $\n, %ebx
   imul $4, %ebx
   subl %ebx, %eax
   movl (%eax), %eax
   pushl %eax
.endm

# -----------------------------------------------------------------
#  ARMZ
# -----------------------------------------------------------------

.macro ARMZ m n
   popl %ecx
   movl $\m, %edi
   movl D(,%edi,4), %eax
   movl $\n, %ebx
   imul $4, %ebx
   subl %ebx, %eax
   movl %ecx, (%eax)

.endm


# -----------------------------------------------------------------
#  CREN
# -----------------------------------------------------------------

.macro CREN m n
   movl $\m, %edi
   movl D(,%edi,4), %eax
   movl $\n, %ebx
   imul $4, %ebx
   subl %ebx, %eax
   pushl %eax
.endm

# -----------------------------------------------------------------
#  CRVI
# -----------------------------------------------------------------

.macro CRVI m n
   movl $\m, %edi
   movl D(,%edi,4), %eax
   movl $\n, %ebx
   imul $4, %ebx
   subl %ebx, %eax
   movl (%eax), %eax
   movl (%eax), %eax
   pushl %eax
.endm

# -----------------------------------------------------------------
#  ARMI
# -----------------------------------------------------------------

.macro ARMI m n
   popl %ecx
   movl $\m, %edi
   movl D(,%edi,4), %eax
   movl $\n, %ebx
   imul $4, %ebx
   subl %ebx, %eax
   movl (%eax), %eax
   movl %ecx, (%eax)
.endm

# -----------------------------------------------------------------
#  ENRT
# -----------------------------------------------------------------

.macro ENRT j n
   movl $\n, %eax
   subl $1, %eax
   imul $4, %eax
   movl $\j, %edi
   movl D(,%edi,4), %ebx
   subl %ebx, %eax
   movl %eax, %esp
.endm

# -----------------------------------------------------------------
#  NADA
# -----------------------------------------------------------------

.macro NADA 
   nop
.endm

# -----------------------------------------------------------------
#  DSVS
# -----------------------------------------------------------------

.macro DSVS rot
   jmp \rot
.endm

# -----------------------------------------------------------------
#  DSVF
#  Se topo da pilha == 0, entao desvia para rot,
#                          senao segue
#  Implementação complicada.
#  - chama _dsvf com a pilha na seguinte situaçao:
#      valor booleano (%ecx)
#      endereco de retorno se topo=0 (%ebc)
#      endereco de retorno se topo=1 (%eax)
#  - basta empilhar [%eax, %ebx] de acordo com %ecx e "ret"
#
# -----------------------------------------------------------------

.macro DSVF rot
   pushl $\rot
   call _dsvf
.endm

_dsvf:   
   popl %eax  
   popl %ebx  
   popl %ecx
   cmpl $0, %ecx
   je  _dsvf_falso
   pushl %eax   
   ret
_dsvf_falso:
   pushl %ebx 
   ret
   
# -----------------------------------------------------------------
#  DSVR - Desvia para rótulo
#
# -----------------------------------------------------------------

.macro DSVR rot j k
   pushl $\j
   pushl $\k
   call _dsvr
   jmp \rot
.endm

 _dsvr:
    popl %eax # k
    popl %ebx # j

    pushl %eax
    pushl %eax
    ret


# -----------------------------------------------------------------
#  IMPR
# -----------------------------------------------------------------

.macro IMPR
   pushl $strNumOut
   call printf
   addl $8, %esp
.endm

# -----------------------------------------------------------------
#  LEIT
# -----------------------------------------------------------------

.macro LEIT
   pushl $entr
   pushl $strNumIn
   call scanf
   addl $8, %esp
   pushl entr
.endm

# -----------------------------------------------------------------
#  SOMA
# -----------------------------------------------------------------

.macro SOMA
   popl %eax
   popl %ebx
   addl %eax, %ebx
   push %ebx
.endm

# -----------------------------------------------------------------
#  SUBT
# -----------------------------------------------------------------

.macro SUBT
   popl %eax
   popl %ebx
   subl %eax, %ebx
   push %ebx
.endm

# -----------------------------------------------------------------
#  MULT
# -----------------------------------------------------------------

.macro MULT
   popl %eax
   popl %ebx
   imul %eax, %ebx
   push %ebx
.endm
      
# -----------------------------------------------------------------
#  DIVI
# A divisão no intel é esquisita. O comando divl não usa dois
# operandos, mas sim um. A instrução assume que a divisão é do par
# %edx:%eax (64 # bits) pelo parâmetro. O quociente vai em %eax e o
# resto vai # para %edx.
# -----------------------------------------------------------------

.macro DIVI
   popl %edi     # divisor
   popl %eax     # dividendo
   movl $0, %edx # não pode esquecer de zerar %edx quando não o usar.
   idiv %edi     #  faz %edx:%eax / %edi
   push %eax     # empilha o resultado
.endm
      
# -----------------------------------------------------------------
#  INVR
# -----------------------------------------------------------------

.macro INVR
   popl %eax
   imul $-1, %eax
   push %eax
.endm
      
# -----------------------------------------------------------------
#  CONJ (E)
# -----------------------------------------------------------------

.macro CONJ
   popl %eax
   popl %ebx
   and  %eax, %ebx
   push %ebx
.endm
      
# -----------------------------------------------------------------
#  DISJ (OU)
# -----------------------------------------------------------------

.macro DISJ
   popl %eax
   popl %ebx
   or   %eax, %ebx
   push %ebx
.endm
      
# -----------------------------------------------------------------
#  NEGA (not)
# -----------------------------------------------------------------

.macro NEGA
   popl %eax
   movl $1, %ebx
   subl %eax, %ebx
   movl %ebx, %eax
   push %eax
.endm

# -----------------------------------------------------------------
#  CMME
# -----------------------------------------------------------------

.macro CMME
   popl %eax
   popl %ebx
   call _cmme
   pushl %ecx
.endm

_cmme:
   cmpl %eax,  %ebx   
   jl _cmme_true
   movl $0, %ecx
   ret
_cmme_true:
   movl $1, %ecx
   ret


# -----------------------------------------------------------------
#  CMMA
# -----------------------------------------------------------------

.macro CMMA
   popl %eax
   popl %ebx
   call _cmma
   pushl %ecx
.endm

_cmma:
   cmpl %eax,  %ebx   
   jg _cmma_true
   movl $0, %ecx
   ret
_cmma_true:
   movl $1, %ecx
   ret

   
# -----------------------------------------------------------------
#  CMIG
# -----------------------------------------------------------------

.macro CMIG
   popl %eax
   popl %ebx
   call _cmig
   pushl %ecx
.endm

_cmig:
   cmpl %eax,  %ebx   
   je _cmig_true
   movl $0, %ecx
   ret
_cmig_true:
   movl $1, %ecx
   ret

# -----------------------------------------------------------------
#  CMDG
# -----------------------------------------------------------------

.macro CMDG
   popl %eax
   popl %ebx
   call _cmdg
   pushl %ecx
.endm

_cmdg:
   cmpl %eax,  %ebx   
   jne _cmdg_true
   movl $0, %ecx
   ret
_cmdg_true:
   movl $1, %ecx
   ret

# -----------------------------------------------------------------
#  CMEG
# -----------------------------------------------------------------

.macro CMEG
   popl %eax
   popl %ebx
   call _cmeg
   pushl %ecx
.endm

_cmeg:
   cmpl %eax,  %ebx   
   jle _cmle_true
   movl $0, %ecx
   ret
_cmle_true:
   movl $1, %ecx
   ret


# -----------------------------------------------------------------
#  CMAG
# -----------------------------------------------------------------

.macro CMAG
   popl %eax
   popl %ebx
   call _cmag
   pushl %ecx
.endm

_cmag:
   cmpl %eax,  %ebx   
   jge _cmge_true
   movl $0, %ecx
   ret
_cmge_true:
   movl $1, %ecx
   ret

   

# -----------------------------------------------------------------
# CHPR p,m { M[s+1]:=i+1; M[s+2]:=m; s:= s+2;  i:=p}
#
# Alterado para: CHPR p,m { M[s+1]:=m; M[s+2]:=i+1; s:= s+2;  i:=p}
# 
# CHPR - A implementação de chamadas de procedimento é diferente da
# proposta original do livro. O problema é como guardar o ER e depois
# disso guardar k. É possível fazer, porém fica muito complicado (até
# na volta do procedimento). Por isso, optei por fazer uma
# implementação diferente. Primeiro vai "k" e depois "ER". Isso
# implica em alterações na implementação de ENPR, RTPR e DSVR - mas
# não no nível de geração de comandos. Os mesmos comandos MEPA
# funcionam aqui igual ao que funcionariam na idéia original (exceto
# pela inverção de k e ER, evidentemente).
# -----------------------------------------------------------------

.macro CHPR rot k
   pushl $\k
   call \rot
.endm


# -----------------------------------------------------------------
# 
# ENPR k { s++; M[s]:=D[k]; D[k]:=s+1 }
#
# -----------------------------------------------------------------

.macro ENPR k
   movl $\k, %edi
   movl D(,%edi,4), %eax
   pushl %eax
   movl %esp, %eax
   subl $4, %eax
   movl %eax, D(,%edi,4)
.endm

# -----------------------------------------------------------------
# original: RTPR k,n { D[k]:=M[s]; i:=M[s-2];  s:=s-(n+3) }
# adaptado: RTPR k,n { D[k]:=pop;  i:=pop; lixo:=pop; s:=s-n }
# -----------------------------------------------------------------

.macro RTPR k n
   popl %eax # D[k] salvo
   popl %ebx # ER. Tem que salvar enquanto libera o resto da pilha
   popl %ecx # k do chamador (a ser jogado fora)

   movl $\k, %edi
   movl %eax, D(,%edi,4)

   movl $\n, %eax
   imul $4, %eax
   addl %eax, %esp # esp <- esp - eax
   pushl %ebx      # restaura ER para poder fazer "i=M[s-1]"="ret"
   ret
.endm


# -----------------------------------------------------------------
#  Macros para depuração
# -----------------------------------------------------------------

# -----------------------------------------------------------------
# Imprime tracos para indicar passagem
# -----------------------------------------------------------------

.macro IMPRQQ
  pushl $strTR
  call printf
  addl $4, %esp
.endm
  


# -----------------------------------------------------------------
#  impime_RA
#       k = nivel lexico do ra
#       n = numero de parametros
#       v = numero de vars simples
# -----------------------------------------------------------------
 .macro imprime_RA k,n,v
RT:       pushl $\k
    pushl $\n
    pushl $\v
    call _imprime_RA
 .endm
 
 _imprime_RA:
   popl %ebx  # ER
   popl %ecx  # v
   popl %edx  # n
   popl %edi  # k
   movl D(,%edi,4), %eax
   pushl $strIniRA
   call printf
   addl $4, %esp
   
_impr_vars_locais:   
   cmpl $0, %ecx
   jge _fim_vars_locais
   pushl (%eax)
   pushl $strHEX
   call printf
   addl $8, %esp
_fim_vars_locais: 
   push %ebx
   ret



# *****************************************************************
# FIM macros
# *****************************************************************



.section .data
.equ TAM_D, 10
.lcomm D TAM_D
   

entr: .int 0
strNumOut: .string "%d\n"
strNumIn: .string "%d"
strIniRA: .string "----- strIniRA  --------\n"
strTR: .string "-----\n"
strHEX:   .string "%X\n"


.section .text
.equ FIM_PGMA, 1
.equ SYSCALL, 0x80 

.globl _start
_start:

.include "MEPA"


   

