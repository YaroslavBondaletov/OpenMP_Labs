# Лабораторная работа 3 (Задача 5)

#Генерация файла кординат для работы программы
Пример генерации в powershell

$N = 100000
" $N" | Out-File -Encoding ascii points.txt
1..$N | ForEach-Object {
    $x = Get-Random -Minimum 0.0 -Maximum 100.0
    $y = Get-Random -Minimum 0.0 -Maximum 100.0
    $z = Get-Random -Minimum 0.0 -Maximum 100.0
    "$x $y $z"
} | Out-File -Append -Encoding ascii points.txt

## Сборка
В Visual Studio: Сборка → Собрать решение
Или в терминале:
cd C:\Users\Eduard\source\repos\OpenMP_Labs\lab3\task5_loop\task5_loop
cl /openmp /EHsc /O2 task5_loop

и

cd C:\Users\Eduard\source\repos\OpenMP_Labs\lab3\task5_sections\task5_sections
cl /openmp /EHsc /O2 \task5_sections

## Запуск решения task5_loop
cd C:\Users\Eduard\source\repos\OpenMP_Labs\lab3\task5_loop\x64\Debug
.\task5_loop.exe points.txt 1
.\task5_loop.exe points.txt 4
.\task5_loop.exe points.txt 8

## Запуск решения task5_sections
cd C:\Users\Eduard\source\repos\OpenMP_Labs\lab3\task5_sections\x64\Debug
.\task5_sections.exe points.txt 1
.\task5_sections.exe points.txt 4
.\task5_sections.exe points.txt 8


