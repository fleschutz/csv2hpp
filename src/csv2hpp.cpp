// csv2hpp.cpp - the 'main' code
#include <stdio.h>
#include <string>
#include <algorithm>
#include <cstring>
#include "datatype_hints.hpp" 

const std::string APP_VERSION = "0.7";
const std::string EOL = "<EOL>";

static std::string nextCell(FILE* file)
{
	std::string result = ""; // empty by default

	// skip whitespace
	auto nextChar = fgetc(file);
	while (nextChar == ' ' || nextChar == '\t')
	{
		nextChar = fgetc(file);
	}

	// check for end-of-file
	if (feof(file))
		return EOL; 

	// check for end-of-line
	if (nextChar == '\n' || nextChar == '\r')
	{
		nextChar = fgetc(file);
		if (nextChar != '\n' && nextChar != '\r')
			ungetc(nextChar, file);

		return EOL;
	}

	if (nextChar == ',')
		return ""; // empty cell

	if (nextChar == '\"')
	{
		for (nextChar = fgetc(file); nextChar != '\"'; nextChar = fgetc(file))
		{
			result += nextChar;
		}
		nextChar = fgetc(file);
		if (nextChar != ',')
			ungetc(nextChar, file);
		return result;
	}

	while (nextChar != ',' && nextChar != '\n' && nextChar != '\r')
	{
		result += nextChar;
		nextChar = fgetc(file);
	}
	if (nextChar == '\n' || nextChar == '\r')
		ungetc(nextChar, file);
	return result;
}

static std::string getNameInCell(std::string cell)
{
	auto ptr = cell.c_str();
	std::string result = "";

	// skip leading whitespaces:
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;

	// add to variable name:
	while (*ptr != '\0' && *ptr != ' ' && *ptr != '(')
		result += *ptr++;

	return result;
}

static std::string getDatatypeHint(std::string cell)
{
	std::string hint = "";
	
	if (auto ptr = strchr(cell.c_str(), '('))
	{
		for (;;)
		{
			hint += *ptr;
			if (*ptr == ')' || *ptr == '\0')
				break;
			ptr++;
		}
	}
	return hint;
}

// Prints the C/C++ declaration line, e.g. int value; // from column 1 (int)
static bool printDeclaration(const std::string& hint, const std::string& name, int column)
{
	for (auto& datatype_hint : dataset::datatype_hints)
	{
		if (datatype_hint.HINT != hint)
			continue;
		char buf[1024] = "";
		sprintf(buf, datatype_hint.DECLARATION, name.c_str());

		printf("\t%s", buf);

		int numWhitespaces = 35 - strlen(buf);
		for (int i = 0; i < numWhitespaces; i++)
			printf(" ");

		printf("// from column %2d %s\n", column + 1, hint.c_str());
		return true;
	}
	return false;
}

static bool isNumberEmpty(std::string num)
{
	return (num == "" || num == " " || num == "?" || num == "-" || num == "N/A" || num == "Unknown*" || num == "unknown*");
}

static std::string trimFloat(std::string s)
{
	if (isNumberEmpty(s))
		return "00";

	size_t pos = s.find("±");
	if (pos != std::string::npos)
		s = s.substr(0, pos);

	size_t pos2 = s.find("R");
	if (pos2 != std::string::npos)
		s = s.substr(0, pos2);

	size_t pos3 = s.find("r");
	if (pos3 != std::string::npos)
		s = s.substr(0, pos3);

	size_t pos4 = s.find("V");
	if (pos4 != std::string::npos)
		s = s.substr(0, pos4);
	
	if (strchr(s.c_str(), '.')) // has decimal point?
	{
		// removing ending '0''s:
		s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
			return ch != '0';
		}).base(), s.end());
	}
	return s;
}

static bool printValue(std::string hint, std::string value)
{
	for (auto& datatype_hint : dataset::datatype_hints)
	{
		if (datatype_hint.HINT != hint)
			continue;

		if (datatype_hint.TYPE == "TEXT")
			printf("\"%s\"", value.c_str());
		else if (datatype_hint.TYPE == "BOOL")
			printf("%s", (value == "Yes" || value == "Y" || value == "yes" || value == "y" || value == "True" || value == "true" || value == "ON" || value == "on" || value == "1") ? "true" : "false");
		else if (datatype_hint.TYPE == "CARD")
			printf("%s", isNumberEmpty(value) ? "00" : value.c_str());
		else if (datatype_hint.TYPE == "FLOAT")
		{
			if (isNumberEmpty(value))
				printf("00");
			else if (hint == "(float)")
				printf("%sf", trimFloat(value).c_str());
			else
				printf("%s", trimFloat(value).c_str());
		}
		else if (datatype_hint.TYPE[0] == '_')
			printf("%s%s", trimFloat(value).c_str(), datatype_hint.TYPE); // using C++ literal
		else
			return false;

		return true;
	}
	return false;
}

static int readCSVHeader(FILE* file, const char* objectName)
{
	std::string hints[1024] = {};

	// parse CSV header line
	printf("struct %s_data {\n", objectName);
	int i = 0, columns = 0;
	for (auto cell = nextCell(file); cell != EOL; cell = nextCell(file), i++)
	{
		auto name = getNameInCell(cell);
		hints[i] = getDatatypeHint(cell);
		if (hints[i] == "(skip)")
			continue; // skip this column

		if (!printDeclaration(hints[i], name, i))
		{
			fprintf(stderr, "Sorry, the '%s' datatype hint in column #%d is not listed yet in datatype_hints.csv\n", hints[i].c_str(), i + 1);
			return 1;
		}
		columns++;
	}
	printf("};\n\n");

	// parse CSV data cells
	printf("const %s_data %ss[] { // HINT: 00=empty or unknown field\n", objectName, objectName);
	int rows = 0;
	for (; !feof(file); rows++)
	{
		bool gotOne = false;
		i = 0;
		for (auto cell = nextCell(file); cell != EOL; cell = nextCell(file), i++)
		{
			if (hints[i] == "(skip)")
				continue; // skip this column
			if (!gotOne)
				printf("{");
			else
				printf(",");

			if (!printValue(hints[i], cell))
			{
				fprintf(stderr, "Unhandled type for '%s' in column #%d\n", hints[i].c_str(), i);
				return 1;
			}
			gotOne = true;
		}
		if (gotOne)
			printf("},\n");
	}
	printf("}; // (%d columns x %d rows = %d cells)\n\n", columns, rows, columns * rows);
	return 0;
}

static std::string pluralize(const std::string& name)
{
	if (name.empty())
		return name;
	if (name.back() == 'y')
		return name.substr(0, strlen(name.c_str()) - 1) + "ies";
	return name + "s";
}

static int convertCSV2HPP(const char* filename, const char* objectName, const std::string& cmdLine)
{
	auto file = fopen(filename, "r");
	if (!file)
	{
		fprintf(stderr, "Can't open CSV file: %s\n", filename);
		return 1;
	}
	printf("// NOTE: This C/C++ header file has been converted from '%s'\n", filename);
	printf("//       on March 16, 2026 by using csv2hpp %s with command-line:\n", APP_VERSION.c_str());
	printf("//       %s\n", cmdLine.c_str());
	printf("//       (more information at: https://github.com/fleschutz/csv2hpp)\n");
	printf("// USAGE: #include \"%s.hpp\" ... for (auto& %s : dataset::%s) { ...\n",
	    pluralize(objectName).c_str(), objectName, pluralize(objectName).c_str());
	printf("#pragma once\n#include <SI/literals.h>\nusing namespace SI;\n\nnamespace dataset { \n\n");
	int result = readCSVHeader(file, objectName);
	printf("} // namespace dataset\n\n");
	fclose(file);
	return result;
}

std::string cmdLine2string(int argc, char **argv)
{
	std::string result = argv[0];

	for (int i = 1; i < argc; i++)
	{
		result += " ";
		result += argv[i];
	}

	return result;
}

int printHelp()
{
	printf("csv2hpp - Converts a CSV file into a C/C++ header file for easy #include.\n");
	printf("          Version %s of March 16, 2026\n", APP_VERSION.c_str());
	printf("          More information at: https://github.com/fleschutz/csv2hpp\n");
	printf("\n");
	printf("USAGE: csv2hpp <path-to-CSV-file> <name-of-object>\n");
	return 0;
}


int main(int argc, char **argv)
{
	if (argc == 3)
		return convertCSV2HPP(argv[1], argv[2], cmdLine2string(argc, argv));

	return printHelp();
}
