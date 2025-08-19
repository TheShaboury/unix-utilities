# Makefile for Unix utilities

CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Targets
TARGETS = pwd echo cp mv

# Default target
all: $(TARGETS)

# Individual targets
pwd: pwd.c
	$(CC) $(CFLAGS) -o pwd pwd.c

echo: echo.c
	$(CC) $(CFLAGS) -o echo echo.c

cp: cp.c
	$(CC) $(CFLAGS) -o cp cp.c

mv: mv.c
	$(CC) $(CFLAGS) -o mv mv.c

# Clean target
clean:
	rm -f $(TARGETS)

# Install target
install: all
	sudo cp $(TARGETS) /usr/local/bin/

# Uninstall target
uninstall:
	sudo rm -f /usr/local/bin/pwd /usr/local/bin/echo /usr/local/bin/cp /usr/local/bin/mv

.PHONY: all clean install uninstall
