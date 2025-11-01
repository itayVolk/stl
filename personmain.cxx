/*
 * Itay Volk <ivolk@scu.edu>
 * Rushil Kumar <rkumar3@scu.edu>
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

bool sorter(const Person& a, const Person& b){
	if (a.getGender() != b.getGender())
		return a.getGender() < b.getGender();
	return a.getLName() < b.getLName();
}

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
	 
	cout << "BMI category Statistics:" << endl;
	map<string, int> bmiCounts;
	int totalRecords = 0;
	for (auto per : plist){
		totalRecords++;
		for (auto category : BMICategory){
			if(BMI(per.getWeight(), per.getHeight()) <= category.first){
				bmiCounts[category.second]++;
				break;
			}
		}
	}
	cout << fixed << setprecision(2);
	for (auto pair : bmiCounts){
		cout << pair.first << ": " << pair.second << " records (" << pair.second*100.0/totalRecords << "%)" << endl;
	}

	cout << "Sorting by gender then last name:" << endl;
	sort(plist.begin(), plist.end(), sorter);
	for (auto per : plist){
		cout << per << endl;
	}

	cout << "First person at or taller than the target height:" << endl;
	auto it = find_if(plist.begin(), plist.end(), [targetHeight](Person x){return x.getHeight() >= targetHeight;});
	if (it != plist.end())
		cout << *it << ": " << setprecision(2) << it->getHeight() << " >= " << targetHeight << endl;
	else
		cout << "None." << endl;

	cout << "First person at or more than the target weight and of the target gender:" << endl;
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
