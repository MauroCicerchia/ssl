bison -dy micro.y.c
flex micro.l.c
gcc lex.yy.c micro.y.tab.c -o micro
pause