/*
 * Sin-Yaw Wang <swang24@scu.edu>
 */
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include "person.h"

using namespace std;
using namespace csen79;

inline double BMI(const double weight, const double height) {
	return (weight / (height * height)) * 703.0;
}

struct CmpLessBMI {
	const bool operator()(Person x, double y) {return BMI(x.getWeight(), x.getHeight()) < y; }
};

int main(int argc, char *argv[]) {
    std::vector<Person> plist;
    Person p;
	
	constexpr double targetHeight = 70.0;
	constexpr double targetWeight = 150.0;
	const double targetBMI = BMI(targetWeight, targetHeight);
	constexpr Person::Gender targetGender = Person::Female;
	const std::pair<double, string> BMICategory[] = {{18.85, "Underweight"},
	                                         {24.99, "Normal weight"},
											 {29.99, "Overweight"},
											 {1000.0, "Obesity"}};

    while (std::cin >> p)
        plist.push_back(p);

	vector<Person>::iterator it;
	/*
	 * Students to do:
	 * Counter the number of records fall into each of the BMI range. Compute the proportion.  Output the percentage for each range. Use “std::map” to count for each range.
     * Use “std::sort” to sort the vector first by gender and by last name. Output the entire vector using vector iterator.  Note the provided code already overloaded the formatted output operator “<<”.
	 * Find the first person at or taller than “targetHeight”.
	 * Find the first person at or heavier than the “targetWeight” and of the “targetGender.”
     * Find the first person at or more than the “targetBMI.”
	 *
	 * For 1, use "std::map" to collect the count.
	 * For 2 to 5, make use of the C++ "iterator" feature.
	 *
	 * For the above, must use each of the below at least once.
	 * Function pointer, lambda function, and functor
	 */

	 
	 cout << "\n-- BMI Category Statistics --" << endl;
	 map<string, int> bmiCounts;
	 int totalRecords = 0;
	 double personBmi = 0;
	 for (vector<Person>::iterator it = plist.begin(); it!=plist.end(); ++it){
		personBmi = BMI (it->getWeight(), it->getHeight());
		totalRecords++;
		for (const auto& category : BMICategory){
			if(personBmi <= category.first){
				bmiCounts[category.second]++;
				break;
			}
		}
	 }
	cout << fixed << setprecision(2);
	double proportion;
	 for (map<string, int>::iterator it = bmiCounts.begin(); it !=bmiCounts.end(); ++it){
		proportion = 0;
		if (totalRecords > 0) proportion = (static_cast <double>(it->second) / totalRecords) * 100.0;
		cout << it->first << ": " << it->second << " records (" << proportion << "%)" << endl;
	 }



	 sort(plist.begin(), plist.end(), [](const Person& a, const Person& b){
		if (a.getGender() != b.getGender()){
			return a.getGender() < b.getGender();
		}
		return a.getLName() < b.getLName();
	 });
	 cout << "\n Sorting by Gender Then Last Name: " << endl;
	 for (vector<Person>::iterator it = plist.begin(); it != plist.end(); ++it){
		cout << it->getFName() << " " << it->getLName() << endl;
	 }



	cout << "First person at or taller than the target height:" << endl;
	if ((it = find_if(plist.begin(), plist.end(), [targetHeight](Person x) {return x.getHeight() >= targetHeight; })) != plist.end())
		cout << *it << ": " << setprecision(2) << it->getHeight() << " >= " << targetHeight << endl;
	else
		cout << "None." << endl;



	cout << "Person at or more than the target weight and of the target gender:" << endl;
	if ((it = find_if(plist.begin(), plist.end(), [targetWeight, targetGender](Person x) { return x.getWeight() >= targetWeight && x.getGender() == targetGender; })) != plist.end())
		cout << *it << ": " << setprecision(2) << it->getWeight() << " >= " << targetWeight << " && " << it->getGender() << " == " << targetGender << endl;
	else
		cout << "None." << endl;

	cout << "First person at or more than the target BMI:" << endl;
	CmpLessBMI lessFunctor;
	if ((it = lower_bound(plist.begin(), plist.end(), targetBMI, lessFunctor)) != plist.end())
		cout << *it << ": " << setprecision(2) << BMI(it->getWeight(), it->getHeight()) << " >= " << targetBMI << endl;
	else
		cout << "None." << endl;
	return EXIT_SUCCESS;
}
