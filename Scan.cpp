

#include <iostream>
#include <cstdbool>
#include <filesystem>
#include <dirent.h>
#include <cstring>
using namespace std;



const bool DEBUG = false; // Debug boolean for debugging the program

double Get_Directory_Size(const string Directory){ // Function to get the size of the names of the folders in the directory
		DIR *dir;
		struct dirent *ent;
		double Size=0;
		char *FolderName;
		dir=opendir(Directory.c_str());
		while((ent=readdir(dir))!=NULL){
				
				if(ent->d_type==DT_DIR){
						
						
						if(DEBUG){
								cout<<"Reading: "<<ent->d_name<<"\n";
						}
						Size+=strlen(ent->d_name)+1;
						
				}
				

		}
		rewinddir(dir);
		closedir(dir);
		return Size;


}
char* Get_Directory_Names(const string Directory,const double DirectoryNamesSize){ // Function to get the names of the Directorys and put them into memory
		
		DIR *dir;
		struct dirent *ent;
		char *CurrentChar;
		char *DirectoryNames;
		double Size=0;
		double FullSize=0;
		int Buffer=0;
		DirectoryNames=new char(DirectoryNamesSize);
		dir=opendir(Directory.c_str());
		if(DEBUG){
				cout<<"Get Directory Names --------\n";
		}
		while(true){
				ent=readdir(dir);
				if(DEBUG){
						cout<<"Buffer: "<<Buffer<<"\n";
				}
				if(Buffer==DirectoryNamesSize){
						if(DEBUG){
								cout<<"Quiting function\n";
						}
						break;

				}
				if(ent==NULL){
						cout<<"Reached end of directory before buffer\n";
						break;
				}
				
				
				if(ent->d_type==DT_DIR){
						CurrentChar=ent->d_name;
						Size=strlen(CurrentChar);
						if(DEBUG){
								cout<<"Size: "<<Size<<"\n";
								cout<<"Name: "<<CurrentChar<<"\n";
						}
						for(int i=0;i<=Size;i++){
								if(DEBUG){
										cout<<"Current char: "<<*CurrentChar<<"\n";
										cout<<"i: "<<i<<"\n";
								}
								*DirectoryNames=*CurrentChar;
								DirectoryNames++;
								CurrentChar++;
						}
						Buffer+=Size+1;
						*DirectoryNames='\0';
				}

		}
		for(;Buffer>=1;Buffer--,DirectoryNames--);
		if(DEBUG){
				cout<<"Buffer: "<<Buffer<<"\n";
		}

		return DirectoryNames;
}
bool Check_Directory_Exists(string Directory){ // returns true if the directory exists   
		if(filesystem::exists(Directory) && filesystem::is_directory(Directory)){
				return true;
		}
		else{
				return false;
		}
}
int main(const int argc, const char *argv[])

{

		if(DEBUG){
				cout<<"Maximum arguments: "<<2<<"\n";
				cout<<"Argument number: "<<argc<<"\n";
				for(int i=0;i<argc;i++){
						cout<<"Argument: "<<argv[i]<<"\n";
				}
				cout<<"~\n";
		}
			
		if(argc==1){
				cout<<"Invalid arguments\n";
				return 1;
		}
		if (argc==3){
				cout<<"Invalid arguments\n";
				return 1;
		}
		
		
		const string Directory(argv[1]);

		if (Check_Directory_Exists(Directory)==false){
				cout<<"Invalid Directory\n";
				return 1;
		}
		else{
				if(DEBUG){
						cout<<"Directory valid\n";
				}

		}


		cout<<"Scanning Directory "<<Directory<<"...\n";
	    const double Size=Get_Directory_Size(Directory);
		if(DEBUG){
				cout<<"Size: "<<"\n";
		}
		char *NamesList=Get_Directory_Names(Directory,Size);
			
		
		if(DEBUG){
				cout<<"__________\n";
		}
		for(int i=0;i<Size;i++){
				if(*NamesList==NULL){
						cout<<"NULL\n";
				}
				else{
						cout<<*NamesList;
				}
				NamesList++;
		}
		
		return 0;
}



