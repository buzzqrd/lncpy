# lncpy :scissors: :page_with_curl:
Simple C program for copying lines between files

## Installing
Using the `make` utility to compile from source:
```
$ sudo make install
```

## Usage
This program copies and pastes lines in a similar way to Vim.
Line insertions begin after the line that is specified.
The line numbers to specify start at 1 (not 0), which aligns with Vim line numbers.

```
$ lncpy [source lines] [source file] [insert line] [insert file]
```

### Examples:
Copy lines 12-41 (inclusive) from the file *old_code.c* to after line 33 in the file *new_code.c*.
```
$ lncpy 12-41 old_code.c 33 new_code.c
```

Copy line 15 in *logs.txt* to after line 48 in *report.txt*.
```
$ lncpy 15 logs.txt 48 report.txt
```


## Contributing
Contributions to the code are welcome! Just keep in mind that:
-New features should be simple and fit the core functionality
-Code should be in C
-Changes based on personal preference are best left in your fork

## Licence
This software is licenced under the GNU General Public License v3.0.
A copy of the licence should be included with the code.
An online copy of the licence can be found at [https://www.gnu.org/licenses/gpl-3.0.en.html](https://www.gnu.org/licenses/gpl-3.0.en.html)

