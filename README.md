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

## Is buffering controlled by C or Linux pipes?

- This project includes a demonstration program, write_number, which outputs
  data using the write function rather than fwrite. By comparing the behavior of
  write_number with output_numbers, which uses fwrite, we illustrate that the
  buffering mechanism is a characteristic of C's fwrite rather than a feature of
  the Linux system.
- When executed with write, output occurs immediately without buffering delays,
  confirming that Linux pipes are not responsible for buffering behavior.

```bash
./write_number > output.txt
./write_number
```

- By running write_number, you will see immediate output in contrast to the
  buffered behavior of fwrite, further validating that C's standard library
  controls buffering, not the Linux environment itself.

## ISO/IEC 9899:2024 - Programming Languages

- The behavior of output functions in C, including fwrite, is influenced by the
  stream's buffering mode, as defined in the ISO/IEC 9899:2024 standard.
  According to section 7.23.3, this standard specifies:
  - This section outlines the fundamental rules for output operations in C,
    explaining how buffering modes—unbuffered, fully buffered, and line
    buffered—determine when characters are transmitted to or from the host
    environment. These specifications form the underlying framework for all C
    output functions, meaning that the behavior of functions like fwrite,
    printf, and other output functions aligns with this structure.
  - Tools like stdbuf can dynamically modify the buffering behavior of standard
    streams, thereby impacting the behavior of these functions. By adjusting the
    buffering mode, stdbuf influences when data is actually written, conforming
    to the specifications outlined in the standard.

- ISO/IEC 9899:2024 - Information technology — Programming languages — C
  - https://www.open-std.org/jtc1/sc22/wg14/www/docs/n3220.pdf
  - https://www.iso.org/standard/82075.html
