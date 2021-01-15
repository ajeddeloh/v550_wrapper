wrapper.so:
	gcc -g -O0 -shared -fpic -Wall -Wextra -Werror -fanalyzer wrapper.c -o wrapper.so

.PHONY: clean
clean:
	rm wrapper.so
