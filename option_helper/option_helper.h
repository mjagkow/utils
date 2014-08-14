/* 
 * File:   option_helper.h
 * Author: Igor Myagkov - myagkov@physics.msu.ru
 *
 * Created on August 13, 2014, 7:56 PM
 */

#ifndef OPTIONHELPER_H
#define	OPTIONHELPER_H


#include <boost/program_options.hpp>
#include <string>
#include <ostream>


class OptionHelper
{
public:
    friend std::ostream& operator<<(std::ostream& os, const OptionHelper& opt);
    
    
    // Default constructor
    OptionHelper()
        : _visible("Available options")
    { }
       
//    // Constructor with specified option section title. This title is shown 
//    // in the help message
//    OptionHelper(const std::string & title)
//        : _visible(title)
//    { }
    
    // Get functor to add options to the visible options list
    boost::program_options::options_description_easy_init addVisible()
    {
        return _visible.add_options();
    }
    
    // Get functor to add options to the hidden options list
    boost::program_options::options_description_easy_init addHidden()
    {
        return _hidden.add_options();
    }
    
    // Indicate the option to be positional and set its maximum encounter number
    void setPositional(const char * name, int maxCount)
    {
        _positional.add(name, maxCount);
    }
    
    
    // Parse the arguments using previously set option descriptions
    void parse(int argc, char ** argv)
    {
        _options.add(_visible).add(_hidden);
        
        boost::program_options::store(
                boost::program_options::command_line_parser(argc, argv)
                .options(_options).positional(_positional).allow_unregistered()
                .run(), _map
        );
        
        boost::program_options::notify(_map);
    }
    
    
    // Create typed value semantic object
    template<class T>
    static boost::program_options::typed_value<T>* value()
    {
        return boost::program_options::value<T>();
    };
    
    // Create typed value semantic object and specify variable to store option
    // value
    template<class T>
    static boost::program_options::typed_value<T>* value(T * v)
    {
        return boost::program_options::value(v);
    };
    
    
    
    
    //
    // Methods to be used after parsing
    //
    
    // Access option by name
    const boost::program_options::variable_value& operator[](const std::string& name) const
    {
        return _map[name];
    }
    
    // Checks whether this option had been specified
    bool isSet(const std::string & name) const
    {
        return _map.count(name) > 0;
    }
    
    // Get the entire map of options
    const boost::program_options::variables_map & options() const
    {
        return _map;
    }
    

    
private:
    boost::program_options::options_description _visible, _hidden, _options;
    boost::program_options::positional_options_description _positional;
    boost::program_options::variables_map _map;
};


std::ostream& operator<<(std::ostream& os, const OptionHelper& opt);


#endif	/* OPTIONHELPER_H */

