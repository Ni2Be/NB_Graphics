/*

Attention:
Member varalbles of structs are just named "*name*".
Member variables of classes are named "m_*name*", getter and setter
are named "type const *name*()", and "type& *name*()".
If a function is named "void update_*name*()" the function will
set the varable and do either a validity check or to update
the variable there needs more work to be done than just update
the varable.

*/

#include "NB_Test_Application.h"

int main()
{
	NB::NB_Test_Application application;
	application.run();
	exit(EXIT_SUCCESS);

}

