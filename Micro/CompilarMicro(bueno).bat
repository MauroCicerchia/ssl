bison -dy micro.y.c
flex micro.l.c
gcc lex.yy.c -L"C:\GnuWin32\lib" y.tab.c -o micro
pause