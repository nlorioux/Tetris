#include "pch.h"
#include "CppUnitTest.h"
#include "../Tetris/Shape.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestUnitaire
{
	TEST_CLASS(TestUnitaire)
	{
	public:
		
		TEST_METHOD(TestTableauDeForme)
		{
			Assert::AreEqual((int)tableauFormes.size(), 7);
		}
		TEST_METHOD(TestTableauDeForme0)
		{
			for (int i = 0; i < tableauFormes.size(); i++)
			{
				Assert::AreEqual((int)tableauFormes[i].size(), 4);
			}
		}
		TEST_METHOD(TestTableauDeFormeLigne)
		{
			for (int i = 0; i < tableauFormes.size(); i++)
			{
				for (int j = 0; j < tableauFormes[i].size(); j++)
				{
					Assert::AreEqual((int)tableauFormes[i][j].size(), 8);
				}
			}
		}
	};
}
