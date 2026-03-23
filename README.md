CSV2HPP
=======
**This command-line utility converts CSV files (comma-separated values) into C/C++ header files (.hpp) - to #include them and immediately start to develop on structured, well-formed datasets. This skips error-prone steps like file delivering, loading, parsing, converting, and checking.**

▶️ Usage
---------
1. **Export** or download your database in CSV file format, e.g. to: [pizzas.csv](examples/pizzas.csv)
2. **Edit** the CSV file and add datatype hints to the header line, e.g.: `Company, Pizza_Name, Type, Size, Price ($)`
3. **Convert** by executing: `csv2hpp pizzas.csv pizza > pizzas.hpp`.
4. **Add** the generated header file to your project (#include "[pizzas.hpp](examples/pizzas.hpp)") and start to develop.

💡 Hints
--------
* Build csv2hpp by executing: `cd src && cmake . && make` (just requires cmake and a C++ compiler)
* Datatype hints are mapped to C/C++ datatypes as follows: `(std::string)` → `std::string`, `(double)` → `double`, no datatype is a string, `(skip)` skips the entire column. See all 87 supported datatype hints in: [datatype_hints.csv](src/datatype_hints.csv)
* Empty CSV data cells are mapped to "" for strings and to 00 for everything else (as a hint).
* Precision hints such as '±05' are removed in float or double values (not supported in C/C++).
* Supports also big .CSV files: omits whitespaces, removes trailing '0'. It's recommended to use 'const char*' instead of 'std::string' which can break some compilers.
* More examples can be found in the 📁[examples](examples/) subfolder.

🤝 Contributing
----------------
* Contributions, suggestions, and improvements are welcome!
* Open an Issue if you encounter bugs or have feature ideas.
* Create a Pull Request if you'd like to improve something.

📜 License & Copyright
-----------------------
This open source project is licensed under the CC0-1.0 license. All trademarks are the property of their respective owners.
