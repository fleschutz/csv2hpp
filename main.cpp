#include <stdio.h>
#include <string>

std::string nextCell(FILE* file)
{
	std::string result = "";

	auto nextChar = fgetc(file);
	if (nextChar == '\"')
	{
		for (nextChar = fgetc(file); nextChar != '\"'; nextChar = fgetc(file))
		{
			result += nextChar;
		}
	}
	else
	{
		for (nextChar = fgetc(file); nextChar != ','; nextChar = fgetc(file))
		{
			result += nextChar;
		}
	}
	return result;
}

int readCSVHeader(FILE* file)
{
	for (auto cell = nextCell(file); cell != ""; cell = nextCell(file))
	{
		printf("%s, ", cell.c_str());
	}
	printf("\n");
	return 0;
}

int convertFile(const char* filename)
{
	if (auto file = fopen(filename, "rw"))
	{
		readCSVHeader(file);
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
