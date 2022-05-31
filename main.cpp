#include <iostream>
#include <filesystem>
#include <fstream>
#include <memory>


class ITests
{
	public:
	virtual int run ( int ){}
};

class Lucky: public ITests
{
	long count = 0;
	
	public:
	
	Lucky(){}
	~Lucky(){}
	
	virtual int run( int n = 0 )
	{
		count = 0;
		
		getLuckyCount( n , 0 , 0 );
		
		return count;
	}
	
	void getLuckyCount( int n , int sumA , int sumB )
	{
		if( n == 0 )
		{
			if( sumA == sumB )
			count++;
			
			return;		
		}
		
		for( int a = 0; a <= 9; a ++ )
			for( int b = 0; b <= 9; b ++ )
			getLuckyCount( n - 1 , sumA + a , sumB + b );
	}	
};

class Tester
{
	std::string file1_name;
	std::string file2_name;
	
	std::string path;
	
	std::unique_ptr< ITests > itests;
	
	public:
	
	Tester( const std::string& _path , std::unique_ptr< ITests > _itests ) : path( _path ) , itests( std::move( _itests ) ) {}
	~Tester(){}
	
	void RunTests( void )
	{
		int n = 0;
		
		while( true )
		{
			file1_name = path + (std::string)"test." + std::to_string( n ) + (std::string)".in";
			file2_name = path + (std::string)"test." + std::to_string( n ) + (std::string)".out";
			
			
			
			if( !std::filesystem::exists( (std::filesystem::path) file1_name ) || !std::filesystem::exists( (std::filesystem::path) file2_name ) )
			{
				std::cout<<"file not exists!"<<std::endl;
				break;
			}	
			
			RunTest( file1_name , file2_name );
			
			n++;
		}
	}
	
	bool RunTest ( const std::string& file1_name , const std::string& file2_name )
	{
		std::ifstream f_initial_data( file1_name , std::ios::binary );
		std::ifstream f_result( file2_name , std::ios::binary );
		
		char str1[10] = {0};
		char str2[10] = {0};
		
		f_initial_data >> str1;
		
		f_result >> str2;
		
		std::string s1( str1 );
		std::string s2( str2 );
		
		
		int data = std::stoi( s1 );
		
		int expect = std::stoll( s2 );
		
		int actual = itests->run( data );
		
		expect == actual ? std::cout << "true" << " expect = " << expect << " actual " << actual   : std::cout << "false" << " expect = " << expect << " actual " << actual  ;
		
		std::cout << std::endl;
	
		f_initial_data.close();
		f_result.close();
		
		return actual == expect;
	}
	


};

int main ( int argc , char** argv )
{
	std::cout<<"algo2"<<std::endl;
	
	try
	{
	
		
		using namespace std;
		
		Tester test( "" , make_unique<Lucky> ( ) );		
			
		test.RunTests();
		

	}
	catch( ... )
	{
		std::cout<<"error"<<std::endl;
	}
  
  	return 0;
}
