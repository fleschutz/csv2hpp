csv2hpp
=======
This command-line tool converts databases in CSV file format (.CSV suffix) into header files to be included in C++ projects. Please perform the following steps for conversion:

1. Export your database in CSV file format or fetch .CSV files directly.
2. Adjust the CSV header line by adding the C++ datatype or SI literal in round brackets, e.g.: `NAME (string), AGE (int), DISTANCE (_km)`
3. Execute: `./csv2hpp input_file.csv > output_file.hpp`.
4. Include the .hpp file in your software project.

Hints
-----
* (string) gets mapped to 'const char*', (int) gets mapped to 'int', (float) gets mapped to 'float', (double) gets mapped to 'double', (bool) gets mapped to 'bool', (_km) gets mapped to 'SI:length' and so on.
* Empty CSV cells are mapped to "" for strings and to 00 for everything else (as a hint).
* Trailing '0's for float and double are removed (more compact).
* Supports very large .CSV files by using 'const char*' instead of 'std::string' (breaks some compilers) and by omitting whitespaces.
