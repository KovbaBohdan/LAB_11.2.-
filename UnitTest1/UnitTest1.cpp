#include "pch.h"
#include "CppUnitTest.h"
#include "../LAB_11.2.A/lab.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
            const char* testFilename = "test.bin"; 

            ofstream testFile(testFilename, ios::binary);
            if (!testFile.is_open()) {
                Assert::Fail(L"Failed to create test file");
            }

            Student testData[] = {
                {"Surname1", 1,  Õ, 5, 4, 5},
                {"Surname2", 2, ≤Õ, 4, 5, 3},
                {"Surname3", 3, Ã≈, 3, 5, 5},
                {"Surname4", 4, ‘≤, 5, 5, 5},
                {"Surname5", 5, “Õ, 5, 5, 4}
            };

            testFile.write(reinterpret_cast<const char*>(testData), sizeof(testData));
            testFile.close();

            int countInformatics5 = 0, countPhysics5 = 0, countMath5 = 0;
            CountMarks(const_cast<char*>(testFilename), countInformatics5, countPhysics5, countMath5);
            Assert::AreEqual(3, countInformatics5); 
            Assert::AreEqual(3, countPhysics5); 
            Assert::AreEqual(4, countMath5);
		}
	};
}
