#include <stdio.h>
#include <string>
#include <cstring>

const std::string EOL = "<EOL>";

std::string nextCell(FILE* file)
{
	std::string result = ""; // empty by default

	// skip optional space/tab
	auto nextChar = fgetc(file);
	while (nextChar == ' ' || nextChar == '\t')
	{
		nextChar = fgetc(file);
	}

	if (feof(file) || nextChar == '\n' || nextChar == '\r')
		return EOL; // end of line reached

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
	if (auto ptr = strchr(cell.c_str(), '('))
	{
		std::string result = "";
		for (ptr++; *ptr != ')'; )
		{
			result += *ptr++;
		}
		return result;
	}
	return "const char*";
}

void printDatatype(std::string type, std::string name)
{
	if (type == "_km" || type == "_m" || type == "_au" || type == "_pc")
		printf("    SI::length %s;\n", name.c_str());
	else if (type == "_kg")
		printf("    SI::mass %s;\n", name.c_str());
	else if (type == "_s" || type == "_h" || type == "_days")
		printf("    SI::time %s;\n", name.c_str());
	else if (type == "_K" || type == "_degC" || type == "_degF")
		printf("    SI::temperature %s;\n", name.c_str());
	else if (type == "_bar")
		printf("    SI::pressure %s;\n", name.c_str());
	else if (type == "_m_per_s")
		printf("    SI::velocity %s;\n", name.c_str());
	else if (type == "_m_per_s²")
		printf("    SI::acceleration %s;\n", name.c_str());
	else if (type == "_kg_per_m³" || type == "_g_per_cm³")
		printf("    SI::density %s;\n", name.c_str());
	else
		printf("    %s %s;\n", type.c_str(), name.c_str());
}

bool isEmpty(std::string value)
{
	if (value == "" || value == "Unknown*" || value == "unknown*")
		return true;
	return false;
}

void printValue(std::string type, std::string value)
{
	if (type == "const char*")
		printf("\"%s\", ", value.c_str());
	else if (type == "bool")
		printf("%s, ", (value == "Yes" || value == "yes" || value == "True" || value == "true" || value == "1") ? "true" : "false");
	else if (type == "int" && isEmpty(value))
		printf("00, ");
	else if (type == "int")
		printf("%s, ", value.c_str());
	else if (type == "float" && isEmpty(value))
		printf("00, ");
	else if (type[0] == '_' && isEmpty(value))
		printf("00%s, ", type.c_str());
	else if (type[0] == '_' && value.find("±") != std::string::npos)
		printf("%.3f%s, ", atof(value.c_str()), type.c_str());
	else if (type[0] == '_')
		printf("%s%s, ", value.c_str(), type.c_str());
	else
		printf("%s, ", value.c_str());
}

int readCSVHeader(FILE* file)
{
	std::string types[256];

	printf("struct data_entries {\n");
	int i = 0;
	for (auto cell = nextCell(file); cell != EOL; cell = nextCell(file), i++)
	{
		auto name = nameOfCell(cell);
		auto type = typeOfCell(cell);
		printDatatype(type, name);
		types[i] = type;
	}
	printf("};\n\nconst data_entries csv_data[] {\n");

	while (!feof(file))
	{
		printf("{");
		i = 0;
		for (auto cell = nextCell(file); cell != EOL; cell = nextCell(file), i++)
		{
			printValue(types[i], cell);
		}
		printf("},\n");
	}

	printf("};\n\n");
	return 0;
}

int convertFile(const char* filename)
{
	if (auto file = fopen(filename, "rw"))
	{
		printf("// dataset converted from %s by csv2hpp (00=unknown or empty)\n", filename);
		printf("#pragma once\n\n#include <string>\n#include <SI/literals.h>\n\nnamespace SI { namespace dataset { \n\n");
		readCSVHeader(file);
		printf("} } // SI::dataset\n\n");
		fclose(file);
		return 0;
	}
	fprintf(stderr, "Can't open CSV file: %s\n", filename);
	return 1;
}


int main(int argc, char **argv)
{
	if (argc == 2)
		return convertFile(argv[1]);

	fprintf(stderr, "csv2hpp <filename>\n");
	return 0;
}
