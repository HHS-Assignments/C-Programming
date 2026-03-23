# Opgave 2: Compile proces (compact)



## a) compile + link

```powershell
Set-Location "c:\Users\Tom\Git\C-Programming\Les-5\OPD-2"
Remove-Item *.obj,*.exe,*.i -ErrorAction SilentlyContinue
cl /nologo main.c sudoku_io.c sudoku_checks.c /Fe:sudoku_a.exe
```

```text
main.c
sudoku_io.c
sudoku_checks.c
Generating Code...
```

## b) alleen pre compile

```powershell
cl /nologo /P /Fi:main.i main.c
```

```text
main.c
```

## c) alleen compile

```powershell
Remove-Item *.obj -ErrorAction SilentlyContinue
cl /nologo /c main.c sudoku_io.c sudoku_checks.c
```

```text
main.c
sudoku_io.c
sudoku_checks.c
Generating Code...
```

## d) alleen linken

```powershell
link /NOLOGO main.obj sudoku_io.obj sudoku_checks.obj /OUT:sudoku_d.exe
```

```text
(geen extra tekst, command voltooid zonder fout)
```

## e) opnieuw compile + link

```powershell
Remove-Item *.obj, sudoku_e.exe -ErrorAction SilentlyContinue
cl /nologo /c main.c sudoku_io.c sudoku_checks.c
link /NOLOGO main.obj sudoku_io.obj sudoku_checks.obj /OUT:sudoku_e.exe
```

```text
main.c
sudoku_io.c
sudoku_checks.c
Generating Code...
```

## f) minimale rebuild na 1 wijziging

```powershell
cl /nologo /c main.c
link /NOLOGO main.obj sudoku_io.obj sudoku_checks.obj /OUT:sudoku_f.exe
```

```text
main.c
```