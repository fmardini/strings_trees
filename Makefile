%: %.c
	gcc -W -Wall -pedantic -std=c99 -g -ggdb -o $@ $^
