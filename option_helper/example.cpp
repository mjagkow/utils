/* 
 * File:   main.cpp
 * Author: Igor Myagkov - igor.myagkov@cern.ch
 *
 * Created on February 5, 2015, 5:25 PM
 */

#include <cstdlib>
#include <argp.h>

using namespace std;

const char *argp_program_version = "Option example 1.0";

static struct argp_option options[] = {
    {"verbose",  'v', 0,      0,  "Produce verbose output" },
    {"quiet",    'q', 0,      0,  "Don't produce any output" },
    {"silent",   's', 0,      OPTION_ALIAS },
    {"output",   'o', "FILE", 0,  "Output to FILE instead of standard output" },
    { 0 }
};

/*
 * Try Also --help and --version !
 */

struct arguments
{
    char *args[2];                /* arg1 & arg2 */
    int silent, verbose;
    char *output_file;
};

static error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
    // Retrieving current configuration
    struct arguments *arguments = (struct arguments*)state->input;

    switch (key)
    {
    case 'q': case 's':
        arguments->silent = 1;
        break;
    case 'v':
        arguments->verbose = 1;
        break;
    case 'o':
        arguments->output_file = arg;
        break;

    case ARGP_KEY_ARG:
        // Normal, non-key argument
        if (state->arg_num >= 2) /* Too many arguments. */
            argp_usage (state);
        arguments->args[state->arg_num] = arg;
        break;
        
    case ARGP_KEY_END:
        // End of argument stream
        if (state->arg_num < 2) /* Not enough arguments. */
            argp_usage (state);
        break;

    default:
        return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

static struct argp argp = {options, parse_opt};


int main(int argc, char** argv) {
    // Arbitrary structure to store configuration
    struct arguments arguments;

    // Default values
    arguments.silent = 0;
    arguments.verbose = 0;
    arguments.output_file = (char *)"-";
    
    argp_parse(&argp, argc, argv, 0, 0, (void *)&arguments);
    
    printf ("ARG1 = %s\nARG2 = %s\nOUTPUT_FILE = %s\n"
            "VERBOSE = %s\nSILENT = %s\n",
            arguments.args[0], arguments.args[1],
            arguments.output_file,
            arguments.verbose ? "yes" : "no",
            arguments.silent  ? "yes" : "no");

    return 0;
}


