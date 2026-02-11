csv2hpp
=======
**This useful utility converts databases from CSV file format into C/C++ header files (even BIG ones). Afterward, include the header files in your software projects and immediately work on structured, well-formed datasets (and skip CSV file delivering, loading, parsing, converting, etc.).**

👣 Steps
---------
1. **Export** or download the database in CSV file format, e.g. to: `database.csv`
2. **Edit** the CSV file and just add datatype hints to the header line, e.g.: `Name (string), Age (int), Weight (float)`
3. **Convert** by executing: `csv2hpp database.csv name_of_object > headerfile.hpp`.
4. **Add** the header file to your project, add: `#include "headerfile.hpp"` and immediately start developing.

💡 Hints
--------
* Datatype hints are mapped to C/C++ datatypes as follows: `(skip)` skips the column, `(string) -> const char*`, `(int) -> int`, `(float) -> float`, and so on. All supported datatype hints are listed in [hints.csv](src/hints.csv)
* Empty CSV cells are mapped to "" for strings and to 00 for everything else (as a hint).
* Trailing '0's for float and double values are removed (more compact).
* Precision hints (e.g. '±05') are removed for float and double values.
* Supports very large .CSV files by using 'const char*' instead of 'std::string' (breaks some compilers) and by omitting whitespaces.

🎉 Example
-----------
Using [planets.csv](src/planets.csv) and executing: `csv2hpp planets.csv planet > planets.hpp` results in the header file: [planets.hpp](src/planets.hpp).

🤝 Contributing
----------------
* Contributions, suggestions, and improvements are welcome!
* Open an Issue if you encounter bugs or have feature ideas.
* Create a Pull Request if you'd like to improve something.

📜 License & Copyright
-----------------------
This open source project is licensed under the CC0-1.0 license. All trademarks are the property of their respective owners.
