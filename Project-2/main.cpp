#include <iostream>
#include "multiset.h"

using namespace std;

int main()
{
	nonstd::MultiSet<int> mset;
	mset.insert(5);
	mset.insert(3);
	mset.insert(7);
	mset.insert(7);
	mset.insert(5);
	mset.insert(5);

	cout << "The size is: " << mset.size() << endl;
	cout << "3 shows up " << mset.count(3) << " time(s)." << endl;
	cout << mset.contains(3);
}
