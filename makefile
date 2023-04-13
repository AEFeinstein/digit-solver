all:
	gcc .\digits.c -o digits -Wall -Wextra -g

clean:
	-rm digits.exe digits
