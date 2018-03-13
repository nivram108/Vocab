#include <dirent.h>
#include <cstdio>
#include <iostream>
int main()
{
	DIR *dpdf;
	struct dirent *epdf;

	dpdf = opendir("./");
	if (dpdf != NULL){
	   while (epdf = readdir(dpdf)){
		  //printf("Filename: %s",epdf->d_name);
		  std::cout << epdf->d_name << std::endl;
	   }
	}
	closedir(dpdf);
}
