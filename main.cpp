#include <stdio.h>
#include <string>
#include <algorithm>
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


void printDatatype(std::string type, std::string name)
{
	if (type == "string")
		printf("    const char* %s;\n", name.c_str());
	else if (type == "_km" || type == "_m" || type == "_au" || type == "_pc")
		printf("    SI::length %s;\n", name.c_str());
	else if (type == "_kg" || type == "_g" || type == "_t")
		printf("    SI::mass %s;\n", name.c_str());
	else if (type == "_s" || type == "_min" || type == "_h" || type == "_days")
		printf("    SI::time %s;\n", name.c_str());
	else if (type == "_K" || type == "_degC" || type == "_degF")
		printf("    SI::temperature %s;\n", name.c_str());
	else if (type == "_bar" || type == "_mbar")
		printf("    SI::pressure %s;\n", name.c_str());
	else if (type == "_m_per_s" || type == "_km_per_h")
		printf("    SI::velocity %s;\n", name.c_str());
	else if (type == "_m_per_s²")
		printf("    SI::acceleration %s;\n", name.c_str());
	else if (type == "_kg_per_m³" || type == "_g_per_cm³")
		printf("    SI::density %s;\n", name.c_str());
	else
		printf("    %s %s;\n", type.c_str(), name.c_str());
}

bool isNumberEmpty(std::string value)
{
	return (value == "" || value == " " || value == "Unknown*" || value == "unknown*");
}

std::string trimFloat(std::string s)
{
	if (isNumberEmpty(s))
		return "00";
	
	if (strchr(s.c_str(), '.')) // has decimal point?
	{
		// removing ending '0''s:
		s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
			return ch != '0';
		}).base(), s.end());
	}
	return s;
}

void printValue(std::string type, std::string value)
{
	if (type == "string")
		printf("\"%s\",", value.c_str());
	else if (type == "bool")
		printf("%s,", (value == "Yes" || value == "yes" || value == "True" || value == "true" || value == "1") ? "true" : "false");
	else if (type == "int" || type == "long")
		printf("%s,", isNumberEmpty(value) ? "00" : value.c_str());
	else if (type == "float" || type == "double")
		printf("%s,", trimFloat(value).c_str());
	else if (type[0] == '_' && value.find("±") != std::string::npos)
		printf("%.3f%s,", atof(value.c_str()), type.c_str());
	else if (type[0] == '_')
		printf("%s%s,", trimFloat(value).c_str(), type.c_str());
	else
		printf("%s,", value.c_str());
}

int readCSVHeader(FILE* file, const char* objectName)
{
	std::string types[1024];

	printf("struct %s_data {\n", objectName);
	int i = 0;
	for (auto cell = nextCell(file); cell != EOL; cell = nextCell(file), i++)
	{
		auto name = nameOfCell(cell);
		auto type = typeOfCell(cell);
		if (type == "")
		{
			fprintf(stderr, "Please specify a type in round brackets for column #%d\n", i + 1);
			return 1;
		}
		printDatatype(type, name);
		types[i] = type;
	}
	printf("};\n\nconst %s_data %ss[] {\n", objectName, objectName);

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

int convertFile(const char* filename, const char* objectName)
{
	if (auto file = fopen(filename, "rw"))
	{
		printf("// dataset converted from %s by csv2hpp. NOTE: 00=empty (or unknown)\n", filename);
		printf("#pragma once\n\n#include <SI/literals.h>\n\nnamespace SI { namespace dataset { \n\n");
		int result = readCSVHeader(file, objectName);
		printf("} } // SI::dataset\n\n");
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
		fprintf(stderr, "Usage: csv2hpp <filename> <objectname>\n");
		return 1;
	}
	return convertFile(argv[1], argv[2]);
}
