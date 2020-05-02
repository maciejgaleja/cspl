# cspl
Code spell checker

## Usage
### Spell checking
```
cspl check [-i] [-x <spec>]... [-f <file>]
```
Simple `cspl check -f file.txt` will check file and write errors to stdout.

### Interactive mode
Adding `-i` flag will enable interactive mode in which program will ask you to correct errors.

### Filters
```
cspl check -x "/* */" -f main.c
```
will spell check comments in `main.c`.

## Dictionaries
This program uses `hunspell` library and needs compatible dictionaries. Currently dictionary search path is `C:\Hunspell`.

Apart from standard dictionary, cspl allows use of a custom dictionary which is simply a text file with words (one per line).

Custom dictionary is built by searching filesystem from current location until root (like `clang-format` search mode).
The custom word set is extended with contents each file that was found.

In interactive mode, there is an option to add a word to dictionary and select which one to use.

### Creating a dictionary
NOT IMPLEMENTED YET.
Simply create file called .xx_XX.cspl (where xx_XX is language code, e.g. en_US) by hand.
