#include <iostream>

#include "params.h"
#include "utility.h"

// * parsing of parameters

void Params::parse(int argc, char* argv[]) {
	bool endOfOptions = false;
	for (int i = 1; i < argc; i++) { // ignores first arg (program)
		std::string arg(argv[i]);
		std::string nextArg = "";
		if (i < argc - 1) {
			nextArg = std::string(argv[i + 1]);
		}

		bool nextArgUsed = false;
		if (endOfOptions || arg[0] != '-') { // file
			file = arg;
			return;
		}
		else if (arg.length() == 1 || arg[1] != '-') { // short flag
			nextArgUsed = shortFlags(arg, nextArg);
		}
		else if (arg.length() == 2) { // --
			endOfOptions = true;
		}
		else { // long flag
			nextArgUsed = longFlag(arg, nextArg);
		}

		if (nextArgUsed) {
			i++;
		}
	}
}

bool Params::longFlag(std::string& flag, std::string& nextArg) {
	// nextArg is unused, no long flag needs a value
	if (flag == "--help") {
		help = true;
	}
	else {
		throw std::runtime_error("Unrecognized option " + quote(flag));
	}
	return false;
}

// take the rest of this argument, or the next one
std::string getValue(std::string& arg, std::string& nextArg, int valueStart, bool* nextArgUsed) {
	if (arg.length() == valueStart) {
		if (nextArg.length() == 0) {
			throw std::runtime_error("Option " +
				quote(arg.substr(valueStart - 1, 1)) + " requires an argument");
		}
		*nextArgUsed = true;
		return nextArg;
	}
	else {
		return arg.substr(valueStart);
	}
}

bool Params::shortFlags(std::string& flags, std::string& nextArg) {
	bool nextArgUsed = false;
	for (int i = 1; i < flags.length(); i++) {
		char flag = flags[i];
		// boolean options
		if (flag == 'h') {
			help = true;
		}
		// options that need a value
		else if (flag == 's') {
			sep = getValue(flags, nextArg, i + 1, &nextArgUsed);
			break;
		}
		else if (flag == 'n') {
			std::string numStr = getValue(flags, nextArg, i + 1, &nextArgUsed);
			if (numStr.find_first_not_of("0123456789") != std::string::npos) { // not an integer
				throw std::runtime_error("Invalid number argument " + quote(numStr));
			}
			num = std::stoi(numStr);
			if (num == 0) {
				throw std::runtime_error("Number of equilibria must be positive");
			}
			break;
		}
		else {
			throw std::runtime_error("Unrecognized option " +  quote(flags.substr(i, 1)));
		}
	}
	return nextArgUsed;
}


// * CLI

const std::string usageMessage = "Usage: nash [OPTIONS] [FILE]\n";

void printUsage() {
	std::cerr <<
		usageMessage <<
		"Try 'nash --help' for more information.\n";
}

void printHelp() {
	std::cout <<
		usageMessage <<
		"Search for Nash equilibria in a bimatrix game given by FILE.\n" <<
		"Example: nash -n 2 payoffs.txt\n" <<
		"With no FILE, read standard input.\n" <<
		"\n" <<
		"  -n NUM        Find up to NUM different equilibria.\n" <<
		"  -s SEP        Specify separator used in FILE. Defaults to whitespace.\n" <<
		"  -h, --help    Print this page.\n" <<
		"\n" <<
		"FILE should contain two M x N payoff matrices separated by an empty line.\n" <<
		"Each matrix consists of M lines, each with N numbers separated by SEP.\n";
}