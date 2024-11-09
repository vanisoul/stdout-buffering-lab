# BufferBehaviorTest

This project demonstrates and tests the default buffering behavior of `fwrite`
in C, as well as command-line buffering management using `stdbuf` and `grep` in
various contexts.

## Overview

The project provides examples of:

- Testing default buffering behavior for standard output and file output using
  `fwrite`.
- Manipulating buffering behavior with `stdbuf` for both standard output and
  file output.
- Applying these buffering behaviors in practical command-line usage, including
  with `grep` and its `--line-buffered` option.

## Structure

- **`output_numbers.c`**: A C program that outputs numbers from 1 to 50, with a
  delay of 0.1 seconds between each output using `fwrite`.
- **`number.sh`**: A shell script that outputs numbers from 1 to 50 with `echo`,
  marking even numbers with `###`, and includes a delay of 0.1 seconds.

## Usage

### Testing `fwrite` Default Buffering

1. **Standard Output** Default behavior: line-buffered output for standard
   output.

```bash
./output_numbers
```

2. **File Output** Default behavior: N-sized buffering for file output.

```bash
./output_numbers > output.txt
```

3. **Using `stdbuf` to Modify Buffering** Use `stdbuf` to change the default
   buffering behavior, specifying the buffer size.

```bash
stdbuf -o 4096 ./output_numbers
```

### Applying Buffering Behavior to `grep`

1. **Standard Output with `number.sh`** When using `grep` to filter output,
   standard output is line-buffered by default.

```bash
./number.sh | grep "###"
```

2. **Modifying Buffer Size with `stdbuf`** `stdbuf` can modify `grep`'s buffer
   size.

```bash
./number.sh | stdbuf -o 4096 grep "###"
```

3. **File Output with Modified Buffer Size** Direct output to a file with a very
   small buffer size using `stdbuf`.

```bash
./number.sh | stdbuf -o 1 grep "###" > output.txt
```

### Explanation of `grep --line-buffered` Option

To illustrate the `--line-buffered` option with `grep`, clone the GNU `grep`
repository and inspect the relevant code sections.

- `git clone https://git.savannah.gnu.org/git/grep.git`

The `--line-buffered` option does not modify the underlying buffer structure;
instead, it directly forces a `fflush()` after each line if the option is
enabled.

Relevant code sections:

- Line 1350:

```c
if (line_buffered)
  fflush_errno ();
```

- Line 478:

```c
fflush_errno (void)
{
  if (fflush (stdout) != 0)
    stdout_errno = errno;
}
```
