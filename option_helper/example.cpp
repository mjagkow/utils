/* 
 * File:   example.cpp
 * Author: Igor Myagkov - myagkov@physics.msu.ru
 *
 * Created on August 14, 2014, 7:23 PM
 */
 
// Compile with
// g++ -o example example.cpp option_helper.cpp -std=c++11 -I./ -lboost_program_options

#include <iostream>
#include <string>
#include <vector>
#include "option_helper.h"



using namespace std;

string version("1.0");


int main(int argc, char** argv) {
    
    OptionHelper opt;
    
    string mode;
    
    opt.addVisible()("help,h", "Display help message");
    opt.addVisible()("version,v", "Display program version");
    opt.addVisible()("mode", OptionHelper::value<string>(&mode), "Set program mode; available options: mode1, mode2, mode3");
    opt.addVisible()("compression,c", OptionHelper::value<int>()->default_value(1), "Set compression level");
    
    opt.addHidden()("config", OptionHelper::value< vector<string> >(), "List of configuration files");
    opt.setPositional("config", -1);
    
    opt.parse(argc, argv);
    

    if(opt.isSet("help"))
    {
        cout << 
            "\nOption helper usage example\n\n" <<
            "Usage: example [options] [config, ...]\n\n" <<
            opt << '\n';
        return 0;
    }
    

    if(opt.isSet("version"))
    {
        cout << version << '\n';
        return 0;
    }
    

    if(opt.isSet("mode"))
        cout << "Mode: " << mode << '\n';


    if(opt.isSet("compression"))
        cout << "Compression level: " << opt["compression"].as<int>() << '\n';
    
 
    if(opt.isSet("config"))
    {
        cout << "\nConfiguration files:\n";
        for (auto conf : opt["config"].as< vector<string> >())
            cout << '\t' << conf << '\n';
    }
    

    cout << '\n' << opt.options().size() << " kinds of options had been set\n";
}
