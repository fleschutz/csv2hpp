#include <stdio.h>
#include <string>
#include <algorithm>
#include <cstring>

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

std::string nameOfCell(std::string cell)
{
	auto ptr = cell.c_str();
	std::string result = "";

	while (*ptr != '\0' && *ptr != ' ')
		result += *ptr++;

	return result;
}

std::string typeOfCell(std::string cell)
{
	std::string result = "";
	
	if (auto ptr = strchr(cell.c_str(), '('))
	{
		for (ptr++; *ptr != ')'; )
		{
			result += *ptr++;
		}
	}
	return result;
}


void printDatatype(int column, std::string hint, std::string name)
{
	std::string datatype = "";

	if (hint == "string" || hint == "str" || hint == "text")
		datatype = "const char*";
	else if (hint == "byte")
		datatype = "unsigned char";
	else if (hint == "_m" || hint == "_km" || hint == "_cm" || hint == "_mm" || hint == "_nm" || hint == "_pm" || hint == "_au" || hint == "_pc")
		datatype = "SI::length";
	else if (hint == "_kg" || hint == "_t" || hint == "_g" || hint == "_mg" || hint == "_Da")
		datatype = "SI::mass";
	else if (hint == "_s" || hint == "_min" || hint == "_h" || hint == "_days")
		datatype = "SI::time";
	else if (hint == "_K" || hint == "_degC" || hint == "_degF")
		datatype = "SI::temperature";
	else if (hint == "_bar" || hint == "_mbar")
		datatype = "SI::pressure";
	else if (hint == "_Hz" || hint == "_kHz" || hint == "_MHz" || hint == "_GHz")
		datatype = "SI::frequency";
	else if (hint == "_m_per_s" || hint == "_km_per_h")
		datatype = "SI::velocity";
	else if (hint == "_m_per_s²" || hint == "_km_per_s²")
		datatype = "SI::acceleration";
	else if (hint == "_kg_per_m³" || hint == "_g_per_cm³")
		datatype = "SI::density";
	else if (hint == "_km³_per_s²")
		datatype = "SI::volume_per_time_squared";
	else if (hint == "skip")
		return; // skip this column
	else
		datatype = hint;

	printf("\t%s %s;", datatype.c_str(), name.c_str());
	auto len = strlen(datatype.c_str()) + strlen(name.c_str());
	for (int i = 0; i < 40 - len; i++)
		printf(" ");
	printf("// column %2d (%s) in CSV file\n", column + 1, hint.c_str());
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
	if (hint == "string")
		printf("\"%s\",", value.c_str());
	else if (hint == "bool")
		printf("%s,", (value == "Yes" || value == "yes" || value == "True" || value == "true" || value == "1") ? "true" : "false");
	else if (hint == "int" || hint == "long")
		printf("%s,", isNumberEmpty(value) ? "00" : value.c_str());
	else if (hint == "float" || hint == "double")
		printf("%s,", trimFloat(value).c_str());
	else if (hint[0] == '_')
		printf("%s%s,", trimFloat(value).c_str(), hint.c_str());
	else
		printf("%s,", value.c_str());
}

int readCSVHeader(FILE* file, const char* objectName)
{
	std::string hints[1024] = {};

	// parse CSV header line
	printf("struct %s_data {\n", objectName);
	int i = 0;
	for (auto cell = nextCell(file); cell != EOL; cell = nextCell(file), i++)
	{
		auto name = nameOfCell(cell);
		auto hint = typeOfCell(cell);
		if (hint == "")
		{
			fprintf(stderr, "Please specify a datatype hint in round brackets for column #%d\n", i + 1);
			return 1;
		}
		printDatatype(i, hint, name);
		hints[i] = hint;
	}
	printf("};\n\n");

	// parse CSV data cells
	printf("const %s_data %ss[] { // NOTE: 00=empty or unknown field\n", objectName, objectName);
	int rows = 0, columns = 0;
	for (; !feof(file); rows++)
	{
		printf("{");
		i = columns = 0;
		for (auto cell = nextCell(file); cell != EOL; cell = nextCell(file), i++)
		{
			if (hints[i] == "skip")
				continue; // skip this column
			printValue(hints[i], cell);
			columns++;
		}
		printf("},\n");
	}
	printf("}; // (%d columns x %d rows = %d cells)\n\n", columns, rows, columns * rows);
	return 0;
}

int convertCSV2HPP(const char* filename, const char* objectName)
{
	if (auto file = fopen(filename, "rw"))
	{
		printf("// DO NOT EDIT! Data source is %s (converted by github.com/fleschutz/csv2hpp 0.3 on 2026-02-04)\n", filename);
		printf("#pragma once\n#include <SI/literals.h>\nusing namespace SI;\n\nnamespace dataset { \n\n");
		int result = readCSVHeader(file, objectName);
		printf("} // namespace dataset\n\n");
		fclose(file);
		return result;
	}
	fprintf(stderr, "Can't open CSV file: %s\n", filename);
	return 1;
}


int main(int argc, char **argv)
{
	if (argc != 3)
	{
		printf("Convert a CSV file into a C/C++ header file for easy #include\n");
		printf("\n");
		printf("Version 0.3 of 2026-02-04 (see also: https://github.com/fleschutz/csv2hpp)\n");
		printf("\n");
		printf("Usage:   csv2hpp <CSV-filename> <object-name>\n");
		return 0;
	}
	return convertCSV2HPP(argv[1], argv[2]);
}
