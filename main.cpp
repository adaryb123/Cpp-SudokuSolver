#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::vector<std::vector<int>> convert_line_to_vector(const std::string& line)
{
	std::vector<std::vector<int>> sudoku;
	sudoku.reserve(9);
	for (size_t i = 0; i < 9; i++)
	{
		sudoku.push_back(std::vector<int>());
		sudoku.reserve(9);
	}

	for (size_t i = 0; i < 9; i++)
		for (size_t j = 0; j < 9; j++)
			sudoku[i].push_back(line.at((i * 9) + j) - '0');
	return sudoku;
}

bool check_local_square_in_vector(const std::vector<std::vector<int>>& sudoku, const int& new_number, const size_t& row_index, const size_t& col_index)
{
	size_t row_start = 0, row_end = 0, col_start = 0, col_end = 0;

	if (row_index < 3)
	{
		row_start = 0;
		row_end = 3;
	}
	else if (3 <= row_index && row_index < 6)
	{
		row_start = 3;
		row_end = 6;
	}
	else if (6 <= row_index && row_index < 9)
	{
		row_start = 6;
		row_end = 9;
	}

	if (col_index < 3)
	{
		col_start = 0;
		col_end = 3;
	}
	else if (3 <= col_index && col_index < 6)
	{
		col_start = 3;
		col_end = 6;
	}
	else if (6 <= col_index && col_index < 9)
	{
		col_start = 6;
		col_end = 9;
	}

	for (size_t i = row_start; i < row_end; i++)
		for (size_t j = col_start; j < col_end; j++)
			if (!(i == row_index && j == col_index))
				if (sudoku[i][j] == new_number)
					return false;

	return true;
}

bool check_if_new_number_valid_in_vector(const std::vector<std::vector<int>>& sudoku, int& new_number, const size_t& row_index, const size_t& col_index)
{
	for (size_t i = 0; i < 9; i++)
	{
		if (i != col_index)
			if (sudoku[size_t(row_index)][size_t(i)] == new_number)
				return false;
	}

	for (size_t i = 0; i < 9; i++)
	{
		if (i != row_index)
			if (sudoku[size_t(i)][size_t(col_index)] == new_number)
				return false;
	}

	return check_local_square_in_vector(sudoku, new_number, row_index, col_index);
}

void print_sudoku_vector(std::vector<std::vector<int>>& sudoku_vector)
{
	for (size_t i = 0; i < 9; i++)
	{
		if (i == 3 || i == 6)
			std::cout << "______________________\n\n";
		for (size_t j = 0; j < 9; j++)
		{
			if (j == 3 || j == 6)
				std::cout << "| ";
			std::cout << sudoku_vector[i][j] << " ";
		}
		std::cout << "\n";
	}
}

bool solve_sudoku_vector(std::vector<std::vector<int>>& sudoku_vector)
{
	for (size_t i = 0; i < 9; i++)
		for (size_t j = 0; j < 9; j++)
			if (sudoku_vector[i][j] == 0)
			{
				for (int k = 1; k < 10; k++)
					if (check_if_new_number_valid_in_vector(sudoku_vector, k, i, j) == true) {
						sudoku_vector[i][j] = k;
						if (solve_sudoku_vector(sudoku_vector))
							return true;
						else
							sudoku_vector[i][j] = 0;
					}
				return false;
			}
	return true;
}

bool check_if_not_unsolveable_at_start(std::vector<std::vector<int>> sudoku)
{
	for (size_t i = 0; i < 9; i++)
		for (size_t j = 0; j < 9; j++)
			if (sudoku[i][j] != 0)
				if (check_if_new_number_valid_in_vector(sudoku, sudoku[i][j], i, j) == false)
					return false;
	return true;
}

std::string convert_to_line(std::vector<std::vector<int>> sudoku)
{
	std::string result;
	for (size_t i = 0; i < 9; i++)
		for (size_t j = 0; j < 9; j++)
			result.append(std::to_string(sudoku[i][j]));

	return result;
}

bool read_main_parameters(int argc, char* argv[], std::string& input_file, std::string& output_file, std::string& file_mode) {
	file_mode = "sdm";
	std::vector<std::string> argList;
	if (argc > 5 || argc == 4 || argc == 2)
		return false;
	else
	{
		for (int i = 0; i < argc; i++)
			argList.push_back(argv[i]);

		if (argc > 1)
		{
			if (argList[1].compare("-o") == 0)
			{
				output_file = argList[2];
				if (argc > 3)
				{
					if (argList[3].compare("-i") == 0)
						input_file = argList[4];
					else
						return false;

				}
			}
			else if (argList[1].compare("-i") == 0)
			{
				input_file = argList[2];
				if (argc > 3)
				{
					if (argList[3].compare("-o") == 0)
						output_file = argList[4];
					else
						return false;
				}
			}
			else if (argc == 3 && argList[1].compare("--check") == 0)
			{
				input_file = argList[2];
				file_mode = "sdx";
			}
			else
				return false;
		}
	}
	return true;
}

bool check_if_input_is_valid(std::string line)
{
	if (line.size() != 81)
		return false;

	for (size_t i = 0; i < 81; i++)
		if (line[i] > '9' || line[i] < '0')
			return false;

	return true;
}

bool solve_sdx_sudoku(std::vector<std::vector<int>>& sudoku_vector, std::vector<std::vector<std::vector<int>>>& candidates)
{
	for (size_t i = 0; i < 9; i++)
		for (size_t j = 0; j < 9; j++)
			if (sudoku_vector[i][j] == 0)
			{
				for (size_t k = 0; k < candidates[i][j].size(); k++) {
					int candidate_number = candidates[i][j][k];
					if (check_if_new_number_valid_in_vector(sudoku_vector, candidate_number, i, j) == true) {
						sudoku_vector[i][j] = candidate_number;
						if (solve_sdx_sudoku(sudoku_vector, candidates))
							return true;
						else
							sudoku_vector[i][j] = 0;
					}
				}
				return false;
			}
	return true;
}

bool read_sdx_input(std::ifstream& file, std::vector < std::vector<int>>& sudoku, std::vector<std::vector<std::vector<int>>>& candidates)
{
	for (size_t i = 0; i < 9; i++)
	{
		sudoku.push_back(std::vector<int>());
		for (size_t j = 0; j < 9; j++)
			sudoku[i].push_back(0);
	}
	candidates.resize(9);
	for (size_t i = 0; i < 9; i++)
		candidates[i].resize(81);

	for (size_t i = 0; i < 9; i++)
		for (size_t j = 0; j < 9; j++)
		{
			std::string cell;
			file >> cell;
			if (cell.at(0) == 'u') {
				sudoku[i][j] = cell[1];
				candidates[i][j].push_back(int(0));
			}
			else
				for (size_t k = 0; k < cell.size(); k++)
				{
					if (cell.at(k) < '0' || cell.at(k) > '9')
						return false;
					else
						candidates[i][j].push_back(cell.at(k) - '0');
				}

		}
	return true;
}

int main(int argc, char* argv[])
{
	std::string input_file_name, output_file_name, file_line, file_mode;
	if (!read_main_parameters(argc, argv, input_file_name, output_file_name, file_mode))
	{
		std::cout << "Invalid number of parameters\n";
		return 1;
	}

	std::ifstream input_file(input_file_name);
	std::ofstream output_file(output_file_name);

	if (!input_file.is_open() && !input_file_name.empty())
	{
		std::cout << "Cannot open input file.\n";
		return 1;
	}
	if (!output_file.is_open() && !output_file_name.empty())
	{
		std::cout << "Cannot open output file.\n";
		return 1;
	}

	if (file_mode.compare("sdm") == 0)
	{
		while (true) {
			std::string line, output;
			if (input_file_name.empty())
				std::cin >> line;
			else
				if (!(std::getline(input_file, line)))
					break;

			if (!check_if_input_is_valid(line))
			{
				std::cout << "Error: Invalid input!\n";
				return 1;
			}

			std::vector<std::vector<int>> sudoku = convert_line_to_vector(line);
			if (!check_if_not_unsolveable_at_start(sudoku)) {
				output = "";
				std::cout << "Sudoku cant be solved!\n";
			}
			else
			{
				if (solve_sudoku_vector(sudoku))
					output = convert_to_line(sudoku);
				else
				{
					output = "";
					std::cout << "Sudoku cant be solved!\n";
				}
			}

			if (output_file_name.empty())
				std::cout << output << "\n";
			else
				if (!(output_file << output << "\n"))
				{
					std::cout << "Error: cannot write to the file!\n";
					return 1;
				}
		}
		if (!input_file.eof()) {
			std::cout << "Error: Cannot read whole input file!\n";
			return 1;
		}
		return 0;
	}
	else if (file_mode.compare("sdx") == 0)
	{
		std::vector<std::vector<int>> sudoku;
		std::vector<std::vector<std::vector<int>>> candidates;
		if (!read_sdx_input(input_file, sudoku, candidates))
		{
			std::cout << "Error: Invalid input!\n";
			return 1;
		}
		else
		{
			if (solve_sdx_sudoku(sudoku, candidates))
				std::cout << "YES";
			else
				std::cout << "NO";

			return 0;
		}
	}
	else {
		std::cout << "Error: Invalid mode!\n";
		return 1;
	}
}