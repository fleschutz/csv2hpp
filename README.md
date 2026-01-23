csv2hpp
=======
This little command-line tool converts databases from CSV file format into header files for C++ projects. It allows to immediately work on large, structured, well-formed datasets without the need of loading, allocating, checking, and converting (everything is done by csv2hpp and the compiler itself). Please perform the following steps for conversion:

1. **Export** the desired database in CSV file format, or directly download and copy the.CSV file.
2. **Add** datatype hints in round brackets to the CSV header line, e.g.: `Name (string), Age (int), Distance (_km)`
3. **Execute:** `./csv2hpp database.csv dataset_object > dataset.hpp`.
4. **Add:** `#include "dataset.hpp"` to your C++ source code, code, and compile.

Hints
-----
* The hints are mapped to C++ datatypes as follows: `(string) -> const char*`, `(int) -> int`, `(long) -> long`, `(float) -> float`, `(double) -> double`, `(bool) -> bool`, `(_km) -> SI:length` and so on.
* Empty CSV cells are mapped to "" for strings and to 00 for everything else (as a hint).
* Trailing '0's for float and double values are removed (more compact).
* Precision hints (e.g. '±05') are removed for float and double values.
* Supports very large .CSV files by using 'const char*' instead of 'std::string' (breaks some compilers) and by omitting whitespaces.

Example
-------
* Input file: [planets.csv](planets.csv)
* Command-line: `csv2hpp planets.csv planet > planets.hpp`
* Resulting output file: [planets.hpp](planets.hpp)
