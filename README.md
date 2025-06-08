# Игра "Жизнь" (Game of Life)

![Screen Recording 2025-06-08 at 8 59 44 PM (online-video-cutter com)](https://github.com/user-attachments/assets/2ae7e36b-4670-4b8d-9017-c71e64fe337d)

## 📝 Описание
Реализация классического клеточного автомата "Игра Жизнь" Джона Конвея на языке C с использованием библиотеки ncurses для отображения в терминале.

Особенности:
- Поле размером 80x25 клеток
- Тороидальная геометрия (края соединены)
- Управление скоростью симуляции
- Визуализация поколений в реальном времени

## 🛠 Установка и запуск

### Требования
- Компилятор C (gcc/clang)
- Библиотека ncurses

### Сборка и запуск (Linux/macOS)
```bash
gcc game_of_life.c -lncurses -o game_of_life
./game_of_life < input.txt

input.txt: 
- a.txt
- b.txt
- c.txt
- d.txt
- e.txt
- f.txt
