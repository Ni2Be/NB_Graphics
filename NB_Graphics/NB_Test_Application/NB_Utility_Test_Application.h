#pragma once

namespace NB
{
	namespace NB_Test
	{
		class NB_Utility_Test_Application
		{
		public:
			NB_Utility_Test_Application() {};
			void run();
		private:
			void call_back_error();
			void no_call_back_error();
		};
	}
}
