csv2hpp
=======
**This utility converts arbitrary CSV database files into C/C++ header files - to #include the generated header files and immediately start to develop on structured, well-formed datasets. This skips the error-prone data file delivering, loading, parsing, converting, etc.**

👣 Steps
---------
1. **Export** or download your database in CSV file format, e.g. to: [POIs.csv](examples/POIs.csv)
2. **Edit** the CSV file and add a datatype hint to each column in the header line, e.g.: `Location (std::string), Latitude (double), Longitude (double)`
3. **Convert** by executing: `csv2hpp POIs.csv POI > POIs.hpp`.
4. **Add** the generated header file to your project (#include "[POIs.hpp](examples/POIs.hpp)") and start to develop.

💡 Hints
--------
* Build csv2hpp by executing: `cd src && cmake . && make` (requires cmake + C++ compiler)
* The datatype hints are mapped to C/C++ datatypes as follows: `(std::string)` → `std::string`, `(double)` → `double`, `(skip)` skips the entire column. See all 87 supported datatype hints in: [datatype_hints.csv](src/datatype_hints.csv)
* Empty CSV data cells are mapped to "" for strings and to 00 for everything else (as a hint).
* Precision hints such as '±05' are removed in float or double values (not supported in C/C++).
* Supports also big .CSV files: omits whitespaces, removes trailing '0'. It's recommended to use 'const char*' instead of 'std::string' which can break some compilers.
* See the 📁[examples](examples/) subfolder for some conversion examples.

🤝 Contributing
----------------
* Contributions, suggestions, and improvements are welcome!
* Open an Issue if you encounter bugs or have feature ideas.
* Create a Pull Request if you'd like to improve something.

📜 License & Copyright
-----------------------
This open source project is licensed under the CC0-1.0 license. All trademarks are the property of their respective owners.
