/*
 * copyright (c) 2016 Zhang Rui <bbcallen@gmail.com>
 *
 * This file is part of jni4android.
 *
 * jni4android is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * jni4android is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with jni4android; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include <iostream>
#include <getopt.h>
#include "bison.j4a.tab.hpp"
#include "ast.hpp"

typedef struct j4a_options
{
    std::vector<std::string> arguments;

    std::string output;

    int compile;
    int help;
} j4a_options;
static j4a_options g_options;

void show_help()
{
    std::cout
        << std::endl
        << "Usage:" << std::endl
        << "    j4a -h" << std::endl
        << "    j4a -c [-o <output_file>] <input_file>" << std::endl
        << std::endl
        << "Startup:" << std::endl
        << "    " << "-c, --compile         " << "compile file." << std::endl
        << "    " << "-h, --help            " << "print this help." << std::endl
        << "    " << "-o, --output          " << "output file." << std::endl
        << std::endl;
}

int parse_options(int argc, const char * argv[])
{
    static struct option long_options[] =
    {
        {"compile", no_argument,        NULL, 'c'},
        {"help",    no_argument,        &g_options.help, 1},
        {"output",  required_argument,  NULL, 'o'},
        {NULL,      0,                  NULL, 0},
    };

    while (true) {
        int option_index = 0;
        int c = getopt_long(argc, (char * const *)argv, "chi:o:", long_options, &option_index);
        if (c == -1) {
            if (optind < argc) {
                g_options.arguments.push_back(argv[optind]);
                optind++;
                if (optind == argc)
                    break;
                continue;
            } else {
                break;   
            }
        }

        switch (c) {
            case 0:
                /* If this option set a flag, do nothing else now. */
                if (long_options[option_index].flag != 0)
                    break;

                std::cout << "option " << long_options[option_index].name << std::endl;
                if (optarg)
                    std::cout << "with arg " << optarg << std::endl;
                std::cout << std::endl;
                break;

            case 'c':
                g_options.compile = 1;
                break;

            case 'h':
                g_options.help = 1;
                show_help();
                return -1;

            case 'o':
                g_options.output = optarg;
                break;
                
            default:
                show_help();
                return -1;
        }
    }

    if (g_options.help) {
        show_help();
        return 1;
    }

    if (g_options.arguments.size() != 1) {
        show_help();
        return -1;
    }

    if (g_options.arguments[0].empty()) {
        show_help();
        return -1;   
    }

    return 0;
}

inline bool ends_with(const std::string& value, const std::string& ending)
{
    if (ending.size() > value.size())
        return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

inline std::string get_c_file(const std::string& value)
{
    if (ends_with(value, ".h")) {
        std::string result(value, 0, value.length() - 2);
        return result + ".c";
    } else if (ends_with(value, ".hpp")) {
        std::string result(value, 0, value.length() - 4);
        return result + ".cpp";
    } else if (ends_with(value, ".java")) {
        std::string result(value, 0, value.length() - 5);
        return result + ".c";
    }

    return value + ".c";
}

inline std::string get_h_file(const std::string& value)
{
    if (ends_with(value, ".c")) {
        std::string result(value, 0, value.length() - 2);
        return result + ".h";
    } else if (ends_with(value, ".cpp")) {
        std::string result(value, 0, value.length() - 4);
        return result + ".hpp";
    } else if (ends_with(value, ".java")) {
        std::string result(value, 0, value.length() - 5);
        return result + ".hpp";
    }

    return value + ".h";
}

inline std::string get_j4a_include_file(const std::string& value)
{
    if (ends_with(value, ".c")) {
        std::string result(value, 0, value.length() - 2);
        return result + ".include.j4a";
    } else if (ends_with(value, ".cpp")) {
        std::string result(value, 0, value.length() - 4);
        return result + ".include.j4a";
    } else if (ends_with(value, ".java")) {
        std::string result(value, 0, value.length() - 5);
        return result + ".include.j4a";
    }

    return value + ".include.j4a";
}

inline std::string get_j4a_loader_file(const std::string& value)
{
    if (ends_with(value, ".c")) {
        std::string result(value, 0, value.length() - 2);
        return result + ".loader.j4a";
    } else if (ends_with(value, ".cpp")) {
        std::string result(value, 0, value.length() - 4);
        return result + ".loader.j4a";
    } else if (ends_with(value, ".java")) {
        std::string result(value, 0, value.length() - 5);
        return result + ".loader.j4a";
    }

    return value + ".loader.j4a";
}

int compile(const std::string& input_file)
{
    int ret = 0;

    std::string c_file     = g_options.output;
    std::string h_file     = get_h_file(c_file);

    if (c_file.empty()) {
        c_file = get_c_file(input_file);
        h_file = get_h_file(c_file);
    }

    yyin = fopen(input_file.c_str(), "r");
    if (!yyin) {
        std::cout << "failed to open input file: " << input_file << std::endl;
        return -1;
    }

    ast::Context::instance()->set_j4a_include_file_path(get_j4a_include_file(c_file));
    ast::Context::instance()->set_j4a_loader_file_path(get_j4a_loader_file(c_file));
    ast::Context::instance()->set_h_file_path(h_file.c_str());
    ast::Context::instance()->set_c_file_path(c_file.c_str());

    std::string input_dir_name;
    size_t file_name_pos = input_file.rfind('/');
    if (file_name_pos == std::string::npos) {
        input_dir_name = "./";
    } else {
        input_dir_name = input_file.substr(0, file_name_pos);
    }

    ast::Context::instance()->add_java_package("java.lang.Object");
    ast::Context::instance()->add_java_package("java.lang.String");

    std::cout << "add java path: " << input_dir_name << std::endl;
    ast::Context::instance()->set_java_class_dir(input_dir_name.c_str());

    ret = yyparse();
    fclose(yyin);
    return ret;
}

int link_all()
{
    std::cout << "not implemented" << std::endl;
    return 0;
}

int main(int argc, const char * argv[])
{
    int ret = 0;

    ret = parse_options(argc, argv);
    if (ret)
        return ret;

    if (g_options.compile) {
        return compile(g_options.arguments[0]);
    } else {
        return link_all();
    }
}
