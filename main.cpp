/***********************************************************************
FILE MAIN.CPP CONTAINS EXPERIMENTAL CODE RELATED TO BOOST, FMTLIB & DATE

FILE UTMOST REVIEW DONE ON (06.01.2021) BY ARTUR K. 
***********************************************************************/

#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/program_options.hpp>
#include <fmt/format.h>
#include <date/date.h>

#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>

// There is an issue with fmt/format (fmtlib)
// https://github.com/fmtlib/fmt/issues/795

namespace fs = boost::filesystem;
namespace po = boost::program_options;

void threadMethod()
{
    for ( int i = 0; i < 10; i++ )
    { 
        fmt::print( "Threaded method...\n" );
    }
}

int main( int argc, char* argv[] )
{
    fmt::print( "Welcome to Raspbery PI 4!\n" );

    fmt::print( 
        "Current time and date: {}\n", 
        date::format( "%F %T %Z", date::floor< std::chrono::milliseconds >( std::chrono::system_clock::now() ) ) );

    auto revDate = date::January/6/2021;

    fmt::print( "Revision completed on: {}\n", date::format( "%F", revDate ) );

    fmt::print( "Day of the week: {}\n", date::format( "%A", revDate ) );

    fmt::print( "Day of the week: {}\n", date::format( "%A", date::weekday{ revDate } ) );

    // For all formats see: https://howardhinnant.github.io/date/date.html#to_stream_formatting

    fmt::print( 
        "Thread available: {}\n", 
        std::thread::hardware_concurrency() );

    po::options_description optDesc;
    po::variables_map varMap;

    int value { 0 };
    std::vector<std::string> fileNames;

    optDesc.add_options()
        ( "help,h", "Some help message here ...") 
        ( "value,v", po::value< int >( &value )->default_value( 75 ), "Value for ..." )
        ( "files,f", po::value< std::vector< std::string > >( &fileNames )->multitoken(), "Files ..." );

    // To print help all you need is to pass --help
    // To set a value you either use --value or -v

    po::store( po::parse_command_line( argc, argv, optDesc ), varMap );
    po::notify( varMap ) ;

    if ( varMap.count( "help" ) )
    {
        std::cout << optDesc << std::endl;
    }

    if ( varMap.count( "value" ) )
    {
        std::cout << varMap[ "value" ].as< int >() << std::endl;
    }

    for (auto i = 0u; i < fileNames.size(); i++)
    {
        fmt::print( "File Name: {}\n", fileNames[ i ] );
    }

    std::thread th( threadMethod );

    std::string fileName { "test.bin" };

    if ( fs::exists( fileName ) )
    {
        fmt::print(
            "File {} already exists, but we will overwrite it.\n", 
            fileName );
    }

    std::string valueStr = "17.5";

    fmt::print( "Lexical cast example 1: {}\n", boost::lexical_cast< std::string >( 10.5f ) );
    fmt::print( "Lexical cast example 2: {}\n", boost::lexical_cast< float >( valueStr ) );

    FILE* pOutFile = nullptr;
    pOutFile = fopen( &fileName[0], "wb" );

    if ( pOutFile )
    {
        fwrite( &value, sizeof( int ), 1, pOutFile );
        fclose( pOutFile );

        fmt::print( "INFO: FILE '{}' CREATED AND WRITTEN\n", fileName );
    }
    else
    {
        fmt::print( "ERROR: COULDN'T CREATE '{}' FILE!\n", fileName );
    }

    th.join();

    return 0;
}
