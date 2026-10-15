В этой папке лежат решения домашних заданий по курсу C++.



Дедлайны:

1. Задание №01 : 02.01 - 02.05 до 19.10.26.

2. Задание №02 : 02.06 - 02.08 до 19.10.26.

3. Задание №03 : 02.09 - 03.04 до 19.10.26.

4. Задание №04 : 03.05 - 03.06 до 19.10.26.



Parameters:

1. Debug compile options:

1.1. `cmake -B build_strict -S . -DCMAKE_BUILD_TYPE=StrictDebug` соответствует вызову компилятора `g++` с повышением строгости компиляции через дополнительный набор флагов, `ASan`, `UBSan`, `-fsanitize`.

1.2. `cmake -B build_strict -S . ` вызывает `g++ --std=c++23 -Wall -Wextra -Wpedantic`.

2. Codestyle: LLVM via clang-format.

3. Static analysis can be performed via `./clang-tidy.sh 02.01`.
