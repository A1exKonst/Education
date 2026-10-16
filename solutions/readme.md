В этой папке лежат решения домашних заданий по курсу C++.



Launch:

1. `git clone`

2. `cd Education/solutions`

3.  `cmake -B build -S . `

4. `cmake --build build`

5. 
	1. Launch example: `./build/task_02.01`.

	2. Automatic launch of all tasks is possible: `./run_tasks.sh build` or `./run_tasks.sh build_strict` 



Parameters:

1. Codestyle: LLVM via clang-format.

2. Static analysis can be performed via `./clang-tidy.sh 02.01`.

3. Debug compile options:

	1. `cmake -B build -S . ` compiles with `g++ --std=c++23 -Wall -Wextra -Wpedantic`.

	2. `cmake -B build_strict -S . -DCMAKE_BUILD_TYPE=StrictDebug` compiles with
		`g++ --std=c++23 -O1 -g
	        -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC
	        -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion
	        -Wfloat-equal -Wformat=2 -Wold-style-cast -Wuseless-cast
	        -Wzero-as-null-pointer-constant -Wsuggest-override -Wnon-virtual-dtor
	        -Wduplicated-branches -Wduplicated-cond -Wlogical-op -Wnull-dereference
	        -Wextra-semi -Wcast-align=strict -Wmissing-declarations -Wctor-dtor-privacy
	        -fanalyzer -fstack-protector-strong
	        -fsanitize=address,undefined,float-divide-by-zero,float-cast-overflow,bounds-strict` .



Deadlines:

1. week_01 (02.01-02.05) until 19.10.26.

2. week_02 (02.06-02.08) until 19.10.26.

3. week_03 (02.09-03.04) until 19.10.26.

4. week_04 (03.05-03.06) until 19.10.26.
