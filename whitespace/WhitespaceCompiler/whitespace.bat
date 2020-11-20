@echo off
whitespace.exe < %1 > %~n1.c
gcc %~n1.c -o %~n1.exe
del %~n1.c