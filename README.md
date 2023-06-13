# Brainfuck 2
Программа "Brainfuck 2" написана на языке программирования Рефал-5λ.
https://github.com/bmstu-iu9/refal-5-lambda

Для компиляции программы нужны библиотеки "stdio", "String" и "Vector" из
Собрания библиотек Boost языка программирования Рефал-5λ.
https://github.com/Aleksandr3Bocharov/Boost-Refal-5-Lambda-Libraries

Программа "Brainfuck 2" интерпретирует код на языке Brainfuck из исходного файла 'filename.bf'
и компилирует его в код на языке C в файл назначения 'filename.bf.c'.


ИСПОЛЬЗОВАНИЕ:
    brainfuck2 [filename[.bf]]


где
    filename        Имя исходного файла и файла назначения.


Имя по умолчанию исходного файла 'brainfuck.bf'
и файла назначения 'brainfuck.bf.c'.


Если исходный файл 'filename.bf' не существует,
то происходит FATAL_ERROR(1) и программа завершает работу.


Файл назначения 'filename.bf.c' будет перезаписан, если он существует.
