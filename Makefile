wrapper.so:
	gcc -g -O0 -shared -fpic -Wall -Wextra -Werror wrapper.c -o wrapper.so
