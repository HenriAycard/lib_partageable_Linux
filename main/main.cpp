
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

	// ===============    DLOPEN() ===============

	cout << "Openning Composant1.so..." << endl;
	void *handle1 = dlopen("./libComposant1.so", RTLD_LAZY);
        if(!handle1){
                cerr<< "Cannot open library: "<< dlerror() << endl;
                exit(EXIT_FAILURE);
        }

	cout << "Openning Composant2.so..." << endl;
        void *handle2 = dlopen("./libComposant2.so", RTLD_LAZY);
        if(!handle2){
                cerr<< "Cannot open library: "<< dlerror() << endl;
                exit(EXIT_FAILURE);
        }


	// initialisation
	int (* value1)(int, int);
	int (* value2)(int, int);
	char * (* version)();
	dlerror();

	// COMPOSANT 1
	*(void **)(&value1) = dlsym(handle1, "_Z10composant1ii");
	const char *dlsym_error_C1 = dlerror();
        if(dlsym_error_C1){
                cerr << "Cannot load symbol composant 1: " << dlerror()<< endl;
                dlclose(handle1);
		dlclose(handle2);
                exit(EXIT_FAILURE);
        }

	// COMPOSANT 2
	*(void **)(&value2) = dlsym(handle2, "_Z10composant2ii");
	const char *dlsym_error_C2 = dlerror();
        if(dlsym_error_C2){
                cerr << "Cannot load symbol composant 2: " << dlerror()<< endl;
                dlclose(handle1);
		dlclose(handle2);
                exit(EXIT_FAILURE);
        }

	// GET VESION
	*(void **)(&version) = dlsym(handle1, "_Z20getComposant1Versionv");

	cout << (*version)() << endl;
        cout << "valeur 1 :" << (*value1)(data1, data2) << " valeur 2 :" << (*value2)(data1,data2) << endl;
	// Close the library
	cout << "Closing library ..." << endl;
        dlclose(handle1);
	dlclose(handle2);

}
