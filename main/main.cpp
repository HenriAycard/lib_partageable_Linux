
#include <iostream>
#include <dlfcn.h>

#include "Composant1.h"
#include "Composant2.h"

using namespace std;

int main(int argc, char ** argv)
{

	int data1=3;
	int data2=5;

	int valeur1;
	int valeur2;

	valeur1=composant1(data1,data2);

	valeur2=composant2(data1,data2);

	std::cout << getComposant1Version() << std::endl;
	std::cout << "valeur 1 :" << valeur1 << " valeur 2 :" << valeur2 << std::endl;

	cout << "Openning main.so..." << endl;
	void *handle = dlopen("./libComposant1.so", RTLD_LAZY);

        if(!handle){
                cerr<< "Cannot open library: "<< dlerror() << endl;
                exit(EXIT_FAILURE);
        }

	// load
	dlerror();
	int (*function)(int, int);
	function = (int (*)(int, int))dlsym(handle, "composant2");
        const char *dlsym_error = dlerror();
	if(dlsym_error){
		cerr << "Cannot load symbol: " << dlerror()<< endl;
		dlclose(handle);
		exit(EXIT_FAILURE);
	}

	cout << "Valeur du Composant: " << function(data1, data2) << endl;

	// Close the library
	cout << "Closing library ..." << endl;
        dlclose(handle);

}
