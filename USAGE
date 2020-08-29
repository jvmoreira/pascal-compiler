1. Só para gerar código MEPA:
> make
> ./compilador teste1.pas
> cat MEPA

2. Para gerar executável:
> ./executa.sh teste1.pas

Este comando deve gerar um monte de erros de sufixo quando executado
nas máquinas do dinf. É aquele problema que citei com máquinas 64
bits. Tem de trocar os sufixos "l" para "q" no arquivo "mepa.s" (movl
=> movq).

Peço a uma alma caridosa que conseguir fazer isso (testando com
*TODOS* os programas de teste), que me mande uma cópia do "mepa64.s",
para eu poder usar nos próximos semestres desta disciplina.

-----------------------------------------------------------------

Para aqueles mais curiosos, verifiquem o arquivo lex.yy.c . Este
arquivo é a implementação em "C" da autômato gerado pelo analisador
léxico ao ler o arquivo "compilador.l". De forma análoga,
"compilador.tab.c" é o autômato a pilha gerado pelo bison ao ler o
arquivo "compilador.y".

Na segunda parte da disciplina, será mostrado como gerar um autômato a
pilha (tabela de ações e de desvios) para uma classe de gramáticas
mais restritas do que esta, porém que segue o mesmo "esquema". 


