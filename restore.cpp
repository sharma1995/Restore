#include <bits/stdc++.h>
using namespace std;

bool move(const char* source, const char* destination)
{
	//cout<<source<<endl;
	//cout<<destination<<endl;
	if(rename(source,destination)==-1)
    {
    	return false;	
    }
    return true;
}

bool remove_file(const char* file_directory)
{
	if(remove(file_directory)){
            return false;
        }
     else 
     	return true; 
}

void print_syntax(char *str)
{
	fprintf(stderr, "SYNTAX ERROR:\nUsage: %s [file to be deleted]\n", str);
    exit(EXIT_FAILURE);
}

void not_deleted(char* str)
{
	fprintf(stderr, "bash: %s: No such file or directory\n", str);
	exit(EXIT_FAILURE);
}

void restoring_error(char* str)
{
	fprintf(stderr, "bash: %s: No such file or directory\n", str);
	exit(EXIT_FAILURE);
}

void metadata_file_deletion_error(const char *str)
{
	fprintf(stderr, "bash: %s: No such file or directory\n", str);
}


int main(int count, char* argv[])
{
	string homeDir=getenv("HOME");
	if(count!=2)
	{
		print_syntax(argv[0]);
	}
	else if(count==2)
	{
		string file_name=argv[1];
		string file_directory=homeDir+"/.local/share/Trash/info/"+file_name+".trashinfo";      //contains the location of trashinfo file 
		string line;
		string source_directory;
		string destination_directory;
		ifstream myfile (file_directory);
		if (myfile.is_open())																//successfully file is opened
		{
			int n=0;
		    while ( getline (myfile,line) )
		    {
		      	if(n==1)
		      	{
		      		destination_directory=line.substr(5);									//previous path of deleted file is saved
		      	}
		      	n++;
		    }
		    myfile.close();
		}
		else 
		{
		  	not_deleted(argv[1]); 														//if file is not deleted previously
		}

		source_directory=homeDir+"/.local/share/Trash/files/"+file_name;	
//		cout<<source_directory<<endl;	
		const char* source=source_directory.c_str();
		const char* destination=destination_directory.c_str();							//current source of the file to be restored 
		bool result=move(source,destination);
		if(result==true)
		{
//			cout<<"remove(file_directory)"<<endl;
			const char* file_directory1=file_directory.c_str();
			bool result=remove_file(file_directory1);
			if (result==false)
			{
				metadata_file_deletion_error(file_directory1);
			}
		}
		else
		{
//			cout<<"restoring_error(destination)"<<endl;
			restoring_error(argv[1]);
		}
	}
}
