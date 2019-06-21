program:
	gcc src/main.c src/tokenize.c src/parse_line.c src/build_tree.c src/execute.c src/print.c src/util.c -o oneliner -lreadline
