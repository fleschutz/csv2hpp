csv2hpp
=======
**This little command-line tool converts databases from CSV file format (.csv suffix) into C/C++ header files. Software projects can #include them and immediately work on large, structured, well-formed datasets. This skips the time-consuming and error-prone steps of data delivering/loading/allocating/checking/converting (done by csv2hpp and the compiler) - it's perfect for new projects.**

♻️ Conversion
--------------
1. **Export** the desired database in CSV file format, or directly download and copy the.CSV file.
2. **Add** datatype hints in round brackets to the CSV header line, e.g.: `Name (string), Age (int), Distance (_km)`
3. **Execute:** `./csv2hpp database.csv dataset_object > dataset.hpp`.
4. **Add:** `#include "dataset.hpp"` to your C/C++ source code and start to develop.

💡 Hints
--------
* Datatype hints are mapped to C++ datatypes as follows: `(string) -> const char*`, `(int) -> int`, `(long) -> long`, `(float) -> float`, `(double) -> double`, `(bool) -> bool`, `(_km) -> SI:length` and so on.
* Empty CSV cells are mapped to "" for strings and to 00 for everything else (as a hint).
* Trailing '0's for float and double values are removed (more compact).
* Precision hints (e.g. '±05') are removed for float and double values.
* Supports very large .CSV files by using 'const char*' instead of 'std::string' (breaks some compilers) and by omitting whitespaces.

🎉 Example
-----------
* Input file: [planets.csv](planets.csv)
* Command-line: `./csv2hpp planets.csv planet > planets.hpp`
* Resulting output file: [planets.hpp](planets.hpp)

🤝 Contributing
----------------
* Contributions, suggestions, and improvements are welcome!
* Open an Issue if you encounter bugs or have feature ideas.
* Create a Pull Request if you'd like to improve something.

📜 License & Copyright
-----------------------
This open source project is licensed under the CC0-1.0 license. All trademarks are the property of their respective owners.
