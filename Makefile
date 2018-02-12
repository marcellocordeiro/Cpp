compiler = g++
flags = -std=c++14 -Wall -Wextra -Werror -pedantic -pedantic-errors -O2

main_name = main
test_name = test

m: compileMain runMain cleanup
t: compileTest runTest cleanup

compileMain:
	@$(compiler) $(flags) $(main_name).cpp -o $(main_name)

compileTest:
	@$(compiler) $(flags) $(test_name).cpp -o $(test_name)

runMain:
	@./$(main_name)

runTest:
	@./$(test_name)

cleanup:
	@rm -f $(main_name) $(test_name)
	
# -f: ignore nonexistent files, never prompt
# @: don't print the command