# Unix Utilities Implementation

This repository contains simple implementations of basic Unix utilities written in C.

## Utilities Implemented

1. **pwd** - Print Working Directory
2. **echo** - Print arguments to stdout
3. **cp** - Copy files
4. **mv** - Move/rename files

## Files Structure

```
unix-utilities/
├── pwd.c          # Print working directory implementation
├── echo.c         # Echo command implementation
├── cp.c           # Copy command implementation
├── mv.c           # Move command implementation
├── Makefile       # Build configuration
└── README.md      # This file
```

## Compilation

### Using Makefile (Recommended)

```bash
# Compile all utilities
make

# Compile individual utilities
make pwd
make echo
make cp
make mv

# Clean compiled files
make clean
```

### Manual Compilation

```bash
gcc -Wall -Wextra -std=c99 -o pwd pwd.c
gcc -Wall -Wextra -std=c99 -o echo echo.c
gcc -Wall -Wextra -std=c99 -o cp cp.c
gcc -Wall -Wextra -std=c99 -o mv mv.c
```

## Usage and Examples

### pwd
Print the current working directory.

```bash
$ ./pwd
/home/user/unix-utilities
```

### echo
Print arguments separated by spaces.

```bash
$ ./echo Hello World
Hello World

$ ./echo "This is a test"
This is a test

$ ./echo
```

### cp
Copy a file from source to destination.

```bash
$ ./cp source.txt destination.txt
$ ./cp /home/user/file.txt /tmp/backup.txt
```

**Features:**
- Preserves file permissions
- Handles read/write errors
- Provides meaningful error messages

### mv
Move/rename a file from source to destination.

```bash
$ ./mv oldname.txt newname.txt
$ ./mv /tmp/file.txt /home/user/moved_file.txt
$ ./mv file.txt /tmp/file.txt
```

**Features:**
- Uses `rename()` system call when possible for efficiency
- Falls back to copy+unlink for cross-filesystem moves
- Preserves file permissions during copy operations
- Provides meaningful error messages

## Implementation Details

### Error Handling
All utilities implement comprehensive error checking:
- Check return values of all system calls
- Use `errno` to provide meaningful error messages with `strerror()`
- Return appropriate exit codes (0 for success, non-zero for failure)

### System Calls Used

**pwd:**
- `getcwd()` - Get current working directory

**echo:**
- No system calls (uses standard library functions)

**cp:**
- `open()` - Open files
- `read()`/`write()` - Copy data
- `fstat()` - Get file permissions
- `close()` - Close file descriptors

**mv:**
- `rename()` - Rename/move files (primary method)
- `open()`/`read()`/`write()`/`close()` - For cross-filesystem moves
- `unlink()` - Remove original file after copying
- `fstat()` - Get file permissions

### Buffer Size
File operations use a 4KB buffer (`BUFFER_SIZE = 4096`) for efficient I/O.

### Standards Compliance
- Code follows C99 standard
- Compiled with strict warning flags (`-Wall -Wextra`)
- Behavior matches standard Unix utilities

## Testing Examples

```bash
# Test pwd
$ ./pwd
/home/user/project

# Test echo
$ ./echo Hello World from custom echo
Hello World from custom echo

# Test cp
$ echo "Hello, World!" > test.txt
$ ./cp test.txt copy.txt
$ cat copy.txt
Hello, World!

# Test mv
$ ./mv copy.txt renamed.txt
$ ls renamed.txt
renamed.txt
$ cat renamed.txt
Hello, World!
```

## Requirements Met

✅ Each utility is implemented as a separate C file  
✅ Proper error checking on all system calls  
✅ Behavior matches Unix specifications  
✅ No object files or executables in repository  
✅ Comprehensive README with compilation instructions  
✅ Example outputs provided  

## Author

Ahmed Shaboury 
SPL01 System Programming in Linux

## License

This project is for educational purposes.
