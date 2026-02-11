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
	// check for C/C++ datatype alias:
	// check for SI units alias:
	if (hint == "km/h")
		return "_km_per_h";
	if (hint == "m/s")
		return "_m_per_s";
	if (hint == "°C")
		return "_degC";
	if (hint == "°F")
		return "_degF";
	return hint;
}

std::string hint2declaration(std::string hint, std::string name)
{
	// check for SI units:
	if (hint == "_m" || hint == "_km" || hint == "_cm" || hint == "_mm" || hint == "_nm" || hint == "_pm" || hint == "_au" || hint == "_pc")
		return "SI::length " + name;
	if (hint == "_kg" || hint == "_t" || hint == "_g" || hint == "_mg" || hint == "_Da")
		return "SI::mass " + name;
	if (hint == "_s" || hint == "_min" || hint == "_h" || hint == "_days" || hint == "_ms")
		return "SI::time " + name;
	if (hint == "_K" || hint == "_degC" || hint == "_degF")
		return "SI::temperature " + name;
	if (hint == "bar" || hint == "_bar" || hint == "_mbar")
		return "SI::pressure " + name;
	if (hint == "_Hz" || hint == "_kHz" || hint == "_MHz" || hint == "_GHz" || hint == "_THz")
		return "SI::frequency " + name;
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

void printDatatype(std::string hint, std::string name, int column)
{
	std::string declaration = hint2declaration(hint, name) + ";";

	for (auto& supported_hint : dataset::supported_hints)
	{
		if (supported_hint.HINT != hint)
			continue;
		declaration = supported_hint.DECLARATION;
		break;
	}
	printf("\t%s", declaration.c_str());

	auto len = strlen(declaration.c_str());
	for (int i = 0; i < 40 - len; i++)
		printf(" ");

	printf("// CSV column %2d (%s)\n", column + 1, hint.c_str());
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

void printValue(std::string hint, std::string value)
{
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

		printDatatype(hints[i], name, i);
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

			printValue(hints[i], cell);
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
	printf("// DO NOT EDIT! File converted from %s on 2026-02-08 by csv2hpp 0.4\n", filename);
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
