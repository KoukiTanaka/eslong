@echo off
python splc.py %~n1.spl > %~n1.c
gcc %~n1.c -lm -o %~n1.exe
del %~n1.c