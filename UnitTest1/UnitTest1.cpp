#include "pch.h"
#include "CppUnitTest.h"

#include "../DftIterator.h"
#include "../BftIterator.h"
#include "../node.h"
#include "../BinarySearchTree.h"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(Test_BinarySearchTree_DefaultConstructor)
		{
			BinarySearchTree t;

			for (size_t i = 0; i < 100; i++)
				Assert::IsFalse(t.contains(i));
		}

		TEST_METHOD(Test_BinarySearchTree_Contains_and_Insert)
		{
			BinarySearchTree t;

			for (size_t i = 0; i < 100; i++)
				Assert::IsFalse(t.contains(i));


			int arr[] = { 100,59,14,2,17,102,120,110 };

			for (size_t i = 0; i < sizeof(arr) / sizeof(int); i++)
				Assert::IsFalse(t.contains(arr[i]));

			for (size_t i = 0; i < sizeof(arr) / sizeof(int); i++)
				t.insert(arr[i]);

			for (size_t i = 0; i < sizeof(arr) / sizeof(int); i++)
				Assert::IsTrue(t.contains(arr[i]));

			srand(time(0));

			int N = rand();

			t.insert(N);
			Assert::IsTrue(t.contains(N));
		}

		TEST_METHOD(Test_BinarySearchTree_Remove)
		{
			BinarySearchTree t;

			size_t counter_of_exceptions = 0;

			for (size_t i = 0; i < 100; i++) {
				try {
					t.remove(i);
				}
				catch (...) {
					counter_of_exceptions++;
				}
			}

			Assert::AreEqual(counter_of_exceptions, 0u);


			int arr[] = { 100,59,14,2,17,102,120,110 };

			for (size_t i = 0; i < sizeof(arr) / sizeof(int); i++) {
				try {
					t.remove(arr[i]);
				}
				catch (...) {
					counter_of_exceptions++;
				}
			}

			Assert::AreEqual(counter_of_exceptions, 0u);

			for (size_t i = 0; i < sizeof(arr) / sizeof(int); i++)
				Assert::IsFalse(t.contains(arr[i]));

			for (size_t i = 0; i < sizeof(arr) / sizeof(int); i++)
				t.insert(arr[i]);

			for (size_t i = 0; i < sizeof(arr) / sizeof(int); i++)
				if (i % 2 == 0)
					t.remove(arr[i]);

			for (size_t i = 0; i < sizeof(arr) / sizeof(int); i++)
				if (i % 2 == 0)
					Assert::IsFalse(t.contains(arr[i]));
				else
					Assert::IsTrue(t.contains(arr[i]));

		}

		TEST_METHOD(Test_BinarySearchTree_DftIterator)
		{
			BinarySearchTree t1;

			int arr[] = { 16,40,66,23,12,14,15,5 };
			int arr_sorted_by_increasing[] = { 5,12,14,15,16,23,40,66 };

			for (size_t i = 0; i < sizeof(arr) / sizeof(int); i++)
				t1.insert(arr[i]);

			DepthIterator di = t1.create_dft_iterator();
			int i = 0;

			for (di; di.has_next(); di.next()) {
				Assert::AreEqual(di.get_value(), arr_sorted_by_increasing[i]);
				i++;
			}
		}

		TEST_METHOD(Test_BinarySearchTree_BftIterator)
		{
			BinarySearchTree t1;

			int arr[] = { 16,40,66,23,12,14,15,5 };
			int arr_sorted_by_levels[] = { 16, 12,40,5,14,23,66,15 };

			for (size_t i = 0; i < sizeof(arr) / sizeof(int); i++)
				t1.insert(arr[i]);

			BreadthIterator bi = t1.create_bft_iterator();
			int i = 0;

			for (bi; bi.has_next(); bi.next()) {
				Assert::AreEqual(bi.get_value(), arr_sorted_by_levels[i]);
				i++;
			}
		}
		TEST_METHOD(Test_BinarySearchTree_CopyConstructor_for_similar_elements)
		{
			BinarySearchTree t1;

			int arr[] = { 100,59,14,2,17,102,120,110 };

			for (size_t i = 0; i < sizeof(arr) / sizeof(int); i++)
				t1.insert(arr[i]);

			BinarySearchTree t2(t1);

			for (size_t i = 0; i < sizeof(arr) / sizeof(int); i++) {
				Assert::IsTrue(t1.contains(arr[i]));
				Assert::IsTrue(t2.contains(arr[i]));
			}
		}
		TEST_METHOD(Test_BinarySearchTree_CopyConstructor_for_similar_structure)
		{
			BinarySearchTree t1;

			int arr[] = { 100,59,14,2,17,102,120,110 };

			for (size_t i = 0; i < sizeof(arr) / sizeof(int); i++)
				t1.insert(arr[i]);

			DepthIterator di1 = t1.create_dft_iterator();
			BreadthIterator bi1 = t1.create_bft_iterator();

			BinarySearchTree t2(t1);

			DepthIterator di2 = t2.create_dft_iterator();
			BreadthIterator bi2 = t2.create_bft_iterator();

			for (; di1.has_next() && di2.has_next(); di1.next(), di2.next())
				Assert::AreEqual(di1.get_value(), di2.get_value());

			Assert::IsFalse(di1.has_next());
			Assert::IsFalse(di2.has_next());

			for (; bi1.has_next() && bi2.has_next(); bi1.next(), bi2.next())
				Assert::AreEqual(bi1.get_value(), bi2.get_value());

			Assert::IsFalse(bi1.has_next());
			Assert::IsFalse(bi2.has_next());
		}
	};
}