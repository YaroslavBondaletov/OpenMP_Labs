# Лабораторная работа 4 (Задача 6)

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
cd C:\Users\Eduard\source\repos\OpenMP_Labs\lab4\task6\task6
cl /openmp /EHsc /O2 task6

## Запуск решения task6
cd C:\Users\Eduard\source\repos\OpenMP_Labs\lab4\task6\x64\Debug
.\task6.exe points.txt 1
.\task6.exe points.txt 4
.\task6.exe points.txt 8


