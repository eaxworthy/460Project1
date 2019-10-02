#include <iomanip>
#include <cstdlib>
#include <map>
#include "LexicalAnalyzer.h"

using namespace std;

static string token_names[] = {	"EOF_T" };

LexicalAnalyzer::LexicalAnalyzer (char * filename)
{
	input.open(filename);
	token = NONE;
	line = lexeme = "a";
	linenum = pos = errors = 0;
	//TODO: initialize listing file, token file, and error filename
	//to filenames based on input file (See way it's done in project writeup)

	// This function will initialize the lexical analyzer class
}

LexicalAnalyzer::~LexicalAnalyzer ()
{
	// This function will complete the execution of the lexical analyzer class
}

token_type LexicalAnalyzer::GetToken ()
{
	token_type t = NONE;
	input >> lexeme;
	// This function will find the next lexeme int the input file and return
	// the token_type value associated with that lexeme
	return t;
}

string LexicalAnalyzer::GetTokenName (token_type t) const
{
	// The GetTokenName function returns a string containing the name of the
	// token passed to it.
	return "";
}

string LexicalAnalyzer::GetLexeme () const
{
	// This function will return the lexeme found by the most recent call to
	// the get_token function
	return "";
}

void LexicalAnalyzer::ReportError (const string & msg)
{
	// This function will be called to write an error message to a file
}
