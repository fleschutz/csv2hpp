// csv2hpp.cpp - the 'main' code
#include <stdio.h>
#include <string>
#include <algorithm>
#include <cstring>
#include "supported_hints.hpp" // <-- hint to datatype mapping

const std::string EOL = "<EOL>";

std::string nextCell(FILE* file)
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

std::string getNameInCell(std::string cell)
{
	auto ptr = cell.c_str();
	std::string result = "";

	while (*ptr != '\0' && *ptr != ' ')
		result += *ptr++;

	return result;
}

std::string getHintInCell(std::string cell)
{
	std::string hint = "";
	
	if (auto ptr = strchr(cell.c_str(), '('))
	{
		for (ptr++; *ptr != ')'; )
		{
			hint += *ptr++;
		}
	}
	return hint;
}

#if 0
std::string hint2declaration(std::string hint, std::string name)
{
	// check for SI units:
	if (hint == "_m_per_s" || hint == "_km_per_h")
		return "SI::velocity " + name;
	if (hint == "m/s²" || hint == "_m_per_s²" || hint == "_km_per_s²")
		return "SI::acceleration " + name;
	if (hint == "kg/m²" || hint == "g/cm³" || hint == "_kg_per_m³" || hint == "_g_per_cm³")
		return "SI::density " + name;
	if (hint == "_J" || hint == "_kJ" || hint == "_MJ" || hint == "_eV")
		return "SI::energy " + name;
	if (hint == "J/mol" || hint == "_J_per_mol" || hint == "_kJ_per_mol")
		return "SI::energy_per_mol " + name;
	if (hint == "km³/s²" || hint == "_km³_per_s²")
		return "SI::volume_per_time_squared " + name;

	return hint + " " + name; // fallback
}
#endif

bool printDeclaration(const std::string& hint, const std::string& name, int column)
{
	for (auto& supported_hint : dataset::supported_hints)
	{
		if (supported_hint.HINT != hint)
			continue;
		char buf[1024] = "";
		sprintf(buf, supported_hint.DECLARATION, name.c_str());

		printf("\t%s", buf);

		auto len = strlen(buf);
		for (int i = 0; i < 40 - len; i++)
			printf(" ");

		printf("// CSV column %2d (%s)\n", column + 1, hint.c_str());
		return true;
	}
	return false;
}

bool isNumberEmpty(std::string num)
{
	return (num == "" || num == " " || num == "?" || num == "-" || num == "Unknown*" || num == "unknown*");
}

std::string trimFloat(std::string s)
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

bool printValue(std::string hint, std::string value)
{
	for (auto& supported_hint : dataset::supported_hints)
	{
		if (supported_hint.HINT != hint)
			continue;

		if (supported_hint.TYPE == "TEXT")
			printf("\"%s\"", value.c_str());
		else if (supported_hint.TYPE == "BOOL")
			printf("%s", (value == "Yes" || value == "yes" || value == "True" || value == "true" || value == "1") ? "true" : "false");
		else if (supported_hint.TYPE == "CARD")
			printf("%s", isNumberEmpty(value) ? "00" : value.c_str());
		else if (supported_hint.TYPE == "FLOAT")
		{
			if (isNumberEmpty(value))
				printf("00");
			else if (hint == "float")
				printf("%sf", trimFloat(value).c_str());
			else
				printf("%s", trimFloat(value).c_str());
		}
		else if (supported_hint.TYPE == "SI")
			printf("%s%s", trimFloat(value).c_str(), hint.c_str());
		else
			return false;

		return true;
	}
#if 0
	if (hint == "string" || hint == "str" || hint == "text" || hint == "char[4]" || hint == "char[8]" || hint == "char[16]" || hint == "char[32]" || hint == "char[64]")
		printf("\"%s\"", value.c_str());
	else if (hint == "byte" || hint == "short" || hint == "int" || hint == "long" || hint == "long long")
		printf("%s", isNumberEmpty(value) ? "00" : value.c_str());
	else if (hint == "float" && isNumberEmpty(value))
		printf("00");
	else if (hint == "float")
		printf("%sf", trimFloat(value).c_str());
	else if (hint == "double" || hint == "long double")
		printf("%s", trimFloat(value).c_str());
	else if (hint == "bool" || hint == "boolean")
		printf("%s", (value == "Yes" || value == "yes" || value == "True" || value == "true" || value == "1") ? "true" : "false");
	else if (hint[0] == '_')
		printf("%s%s", trimFloat(value).c_str(), hint.c_str());
	else
		printf("%s", value.c_str());
#endif
	return false;
}

int readCSVHeader(FILE* file, const char* objectName)
{
	std::string hints[1024] = {};

	// parse CSV header line
	printf("struct %s_data {\n", objectName);
	int i = 0, columns = 0;
	for (auto cell = nextCell(file); cell != EOL; cell = nextCell(file), i++)
	{
		auto name = getNameInCell(cell);
		hints[i] = getHintInCell(cell);
		if (hints[i] == "")
		{
			fprintf(stderr, "Please specify a datatype hint in round brackets for column #%d\n", i + 1);
			return 1;
		}
		if (hints[i] == "skip")
			continue; // skip this column

		if (!printDeclaration(hints[i], name, i))
		{
			fprintf(stderr, "Datatype hint '%s' in column #%d not listed in supported_hints.csv yet\n", hints[i].c_str(), i + 1);
			return 1;
		}
		columns++;
	}
	printf("};\n\n");

	// parse CSV data cells
	printf("const %s_data %ss[] { // NOTE: 00=empty or unknown field\n", objectName, objectName);
	int rows = 0;
	for (; !feof(file); rows++)
	{
		bool gotOne = false;
		i = 0;
		for (auto cell = nextCell(file); cell != EOL; cell = nextCell(file), i++)
		{
			if (hints[i] == "skip")
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

int convertCSV2HPP(const char* filename, const char* objectName)
{
	auto file = fopen(filename, "rw");
	if (!file)
	{
		fprintf(stderr, "Can't open CSV file: %s\n", filename);
		return 1;
	}
	printf("// DO NOT EDIT! File converted from %s on 2026-02-12 by csv2hpp 0.4\n", filename);
	printf("//              (see https://github.com/fleschutz/csv2hpp for details)\n");
	printf("// USAGE: #include \"%ss.hpp\" ... for (auto& %s : dataset::%ss) { ...\n", objectName, objectName, objectName);
	printf("#pragma once\n#include <SI/literals.h>\nusing namespace SI;\n\nnamespace dataset { \n\n");
	int result = readCSVHeader(file, objectName);
	printf("} // namespace dataset\n\n");
	fclose(file);
	return result;
}


int main(int argc, char **argv)
{
	if (argc != 3)
	{
		printf("Converts a CSV file into a C/C++ header file for easy #include.\n");
		printf("\n");
		printf("Version 0.4 of 2026-02-06 (see also: https://github.com/fleschutz/csv2hpp)\n");
		printf("\n");
		printf("Usage:  csv2hpp <CSV-filename> <object-name>\n");
		return 0;
	}
	return convertCSV2HPP(argv[1], argv[2]);
}
