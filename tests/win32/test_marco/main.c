#include <stdio.h>



#include "cp_register.h"
#include "cp_module_dependent.h"





CP_MAIN_MODULE_DEPENDENT_BEGIN(test)

CP_ADD_MODULE_DEPENDENT(cp_test_register, CP_TEST_REGISTER_MARCO(1, "abc"))

CP_MODULE_DEPENDENT_END




int main(int argc, char** argv)
{
	CP_MAIN_MODULE_DEPENDENT(test);
	return 0;
}