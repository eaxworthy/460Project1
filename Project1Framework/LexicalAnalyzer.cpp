RPARENRPARENRPAREN#include <iomanip>
#include <cstdlib>
#include <map>
#include "LexicalAnalyzer.h"

using namespace std;

//The number assigned to the end state from the table should match that
//symbol/literal/whatever in this array
static string token_names[] = {	"EOF_T", "IDENT_T", "NUMLIT_T", "STRLIT_T",
								"LISTOP_T", "CONS_T", "IF_T", "COND_T",
								"ELSE_T", "DISPLAY_T", "NEWLINE_T", "AND_T",
							  	"OR_T", "NOT_T", "DEFINE_T", "NUMBERP_T",
								"LISTP_T", "ZEROP_T", "NULLP_T", "STRINGP_T",
								"PLUS_T", "MINUS_T", "DIV_T", "MULT_T",
								"MODULO_T", "ROUND_T", "EQUALTO_T", "GT_T",
								"LT_T", "GTE_T", "LTE_T", "LPAREN_T", "RPAREN_T"
								"SQUOTE_T", "ERROR_T"
							};

map<string, token_type> token_map = {
	{"EOF_T", EOF_T}, {"IDENT_T", IDENT_T}, {"NUMLIT_T", NUMLIT_T},
	{"STRLIT_T", STRLIT_T}, {"LISTOP_T", LISTOP_T}, {"CONS_T", CONS_T},
	{"IF_T", IF_T}, {"COND_T", COND_T}, {"ELSE_T", ELSE_T},
	{"DISPLAY_T", DISPLAY_T}, {"NEWLINE_T", NEWLINE_T}, {"AND_T", AND_T},
	{"OR_T", OR_T}, {"NOT_T", NOT_T}, {"DEFINE_T", DEFINE_T},
	{"NUMBERP_T", NUMBERP_T}, {"LISTP_T", LISTP_T}, {"ZEROP_T", ZEROP_T},
	{"NULLP_T", NULLP_T}, {"STRINGP_T", STRINGP_T}, {"PLUS_T", PLUS_T},
	{"MINUS_T", MINUS_T}, {"DIV_T", DIV_T}, {"MULT_T", MULT_T},
	{"MODULO_T", MODULO_T}, {"ROUND_T", ROUND_T}, {"EQUALTO_T", EQUALTO_T},
	{"GT_T", GT_T}, {"LT_T", LT_T}, {"GTE_T", GTE_T}, {"LTE_T", LTE_T},
	{"LPAREN_T", LPAREN_T}, {"RPAREN_T", RPAREN_T}, {"SQUOTE_T", SQUOTE_T},
	{"ERROR_T", ERROR_T}
};

map<string, token_type> keyword_map = {
	{"cons", CONS_T}, {"if", IF_T}, {"cond", COND_T}, {"else", ELSE_T},
	{"display", DISPLAY_T}, {"newline", NEWLINE_T}, {"and", AND_T},
	{"or", OR_T}, {"not", NOT_T}, {"define", DEFINE_T}, {"number?", NUMBERP_T},
	{"list?", LISTP_T}, {"zero?", ZEROP_T}, {"null?", NULLP_T},
	{"string?", STRINGP_T}, {"modulo", MODULO_T}, {"round", ROUND_T}
};

//DFA columns
map<char, int> DFA_map = { {' ', 0}, /*{#, 1}*/ {'_',2} ,{'+', 3}, {'-',4}, {'.', 5}, {'>', 6}, {'<',7}, {'=', 8}, {'"', 9}, /*{char(32),10},*/ {'(', 11}, {')',12},  {'\'',13},  {'*',14}, { '/',15}};


vector <vector<int>> DFA =
{
	{ERROR_T, ERROR_T, ERROR_T, ERROR_T, ERROR_T, ERROR_T, ERROR_T, ERROR_T, ERROR_T, ERROR_T, ERROR_T, ERROR_T, ERROR_T, ERROR_T, ERROR_T, ERROR_T},
	{1, 3, ERROR_T, 7, 8, 5, 12, 13, 11, 4, 2, 16, 17, 18, 10, 9},
	{IDENT_T, 2, 2, IDENT_T, IDENT_T, IDENT_T, IDENT_T, IDENT_T, IDENT_T, IDENT_T, 2, IDENT_T, IDENT_T, IDENT_T, IDENT_T, IDENT_T},
	{NUMLIT_T, 3, NUMLIT_T, NUMLIT_T, NUMLIT_T, 6, NUMLIT_T, NUMLIT_T, NUMLIT_T, NUMLIT_T, NUMLIT_T, NUMLIT_T, NUMLIT_T, NUMLIT_T, NUMLIT_T, NUMLIT_T},
	{4, 4, 4, 4, 4, 4, 4, 4, 4, STRLIT_T, 4, 4, 4, 4, 4, 4},
	{ERROR_T, 6, ERROR_T, ERROR_T, ERROR_T, ERROR_T, ERROR_T, ERROR_T, ERROR_T, ERROR_T, ERROR_T, ERROR_T, ERROR_T, ERROR_T, ERROR_T, ERROR_T},
	{NUMLIT_T, 6, NUMLIT_T, NUMLIT_T, NUMLIT_T, NUMLIT_T,  NUMLIT_T, NUMLIT_T, NUMLIT_T, NUMLIT_T, NUMLIT_T, NUMLIT_T, NUMLIT_T, NUMLIT_T, NUMLIT_T, NUMLIT_T},
	{PLUS_T, 3, PLUS_T, PLUS_T, PLUS_T, PLUS_T, PLUS_T, PLUS_T, PLUS_T, PLUS_T, PLUS_T, PLUS_T, PLUS_T, PLUS_T, PLUS_T, PLUS_T},
	{MINUS_T, 3, MINUS_T, MINUS_T, MINUS_T, MINUS_T, MINUS_T, MINUS_T, MINUS_T, MINUS_T, MINUS_T, MINUS_T, MINUS_T, MINUS_T, MINUS_T, MINUS_T},
	{DIV_T, DIV_T, DIV_T, DIV_T, DIV_T, DIV_T, DIV_T, DIV_T, DIV_T, DIV_T, DIV_T, DIV_T, DIV_T, DIV_T, DIV_T, DIV_T},
	{MULT_T, MULT_T, MULT_T, MULT_T, MULT_T, MULT_T, MULT_T, MULT_T, MULT_T, MULT_T, MULT_T, MULT_T, MULT_T, MULT_T, MULT_T, MULT_T},
	{EQUALTO_T, EQUALTO_T, EQUALTO_T, EQUALTO_T, EQUALTO_T, EQUALTO_T, EQUALTO_T, EQUALTO_T, EQUALTO_T, EQUALTO_T, EQUALTO_T, EQUALTO_T, EQUALTO_T, EQUALTO_T, EQUALTO_T, EQUALTO_T},
	{GT_T, GT_T, GT_T, GT_T, GT_T, GT_T, GT_T, GT_T, GTE_T, GT_T, GT_T, GT_T, GT_T, GT_T, GT_T, GT_T},
	{LT_T, LT_T, LT_T, LT_T, LT_T, LT_T, LT_T, LT_T, LTE_T, LT_T, LT_T, LT_T, LT_T, LT_T, LT_T, LT_T},
	{GTE_T, GTE_T, GTE_T, GTE_T, GTE_T, GTE_T, GTE_T, GTE_T, GTE_T, GTE_T, GTE_T, GTE_T, GTE_T, GTE_T, GTE_T, GTE_T},
	{LTE_T, LTE_T, LTE_T, LTE_T, LTE_T, LTE_T, LTE_T, LTE_T, LTE_T, LTE_T, LTE_T, LTE_T, LTE_T, LTE_T, LTE_T, LTE_T},
	{LPAREN_T, LPAREN_T, LPAREN_T, LPAREN_T, LPAREN_T, LPAREN_T, LPAREN_T, LPAREN_T, LPAREN_T, LPAREN_T, LPAREN_T, LPAREN_T, LPAREN_T, LPAREN_T, LPAREN_T, LPAREN_T},
	{RPAREN_T, RPAREN_T, RPAREN_T, RPAREN_T, RPAREN_T, RPAREN_T, RPAREN_T, RPAREN_T, RPAREN_T, RPAREN_T, RPAREN_T, RPAREN_T, RPAREN_T, RPAREN_T, RPAREN_T, RPAREN_T},
	{SQUOTE_T, SQUOTE_T, SQUOTE_T, SQUOTE_T, SQUOTE_T, SQUOTE_T, SQUOTE_T, SQUOTE_T, SQUOTE_T, SQUOTE_T, SQUOTE_T, SQUOTE_T, SQUOTE_T, SQUOTE_T, SQUOTE_T, SQUOTE_T,}

};

LexicalAnalyzer::LexicalAnalyzer (char * filename)
{
	string file_prefix = filename;
	size_t found = file_prefix.find_last_of('.');
	string file_suffix = file_prefix.substr(found, file_prefix.length()-1);
	file_prefix = file_prefix.substr(0,found+1);
	string lfilename = file_prefix + "lst", tfilename = file_prefix + "pl";
	string dfilename = file_prefix + "dbg";

	input.open(filename);
	listingFile.open(lfilename.c_str());
	tokenFile.open(tfilename.c_str());
	debugFile.open(dfilename.c_str());

	//Tests to see if file ends in ''.ss' extension
	if( file_suffix.compare(".ss") != 0 ){
		cout << "Improper input file.\nOnly .ss files are allowed.\n";
		exit(2);
	}

	token = NONE;
	line = lexeme = "";
	linenum = pos = errors = 0;

	// This function will initialize the lexical analyzer class
}

LexicalAnalyzer::~LexicalAnalyzer ()
{
	// This function will complete the execution of the lexical analyzer class
}

token_type LexicalAnalyzer::GetToken ()
{
	token = NONE;
	lexeme = "";

	//Move to next line if done precessing
	if(pos >= line.length()){
		pos = 0;
		linenum++;
		line = input.getline();
		cout << line;
	}

	//TODO: Process lexeme through char checking and DFA
/*
	auto it = token_map.find(lexeme);
	token = it->second;
	tokenFile << GetTokenName(token) << '\t' << lexeme << endl;
	// This function will find the next lexeme in the input file and return
	// the token_type value associated with that lexeme
	*/
	return token;
}

string LexicalAnalyzer::GetTokenName (token_type t) const
{
	// The GetTokenName function returns a string containing the name of the
	// token passed to it.
	return token_names[t];
}

string LexicalAnalyzer::GetLexeme () const
{
	// This function will return the lexeme found by the most recent call to
	// the get_token function
	return lexeme;
}

void LexicalAnalyzer::ReportError (const string & msg)
{
	// This function will be called to write an error message to a file
}
