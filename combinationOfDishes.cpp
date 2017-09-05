// Backtracking_oops.cpp : Defines the entry point for the console application.
//Author: Anirudh Tetali
//Date: 4th Sept. 2017

#include<iostream>
#include<vector>
#include<algorithm>
#include<math.h>
#include<string>
#include<iomanip>
#include<fstream>
#include<sstream>
using namespace std;

//calculates the total price by combination of dishes and if matches, adds to the result_dishes.
void findNumbers(vector<pair<string, double> >& dishes_list, 
	double target_price,vector<vector<pair<string, double> > >& results_list,
	vector<pair<string, double> >& result_dishes, int i)  
{
	// If current target_price is less than 0
	if (target_price < 0)
		return;

	// if we get exact match of Target_price
	if (target_price == 0)
	{
		results_list.push_back(result_dishes);
		return;
	}

	// Recursion for all remaining elements having smaller values of target_price.
	while (i < dishes_list.size() && target_price - dishes_list[i].second >= 0)
	{
		
		if (target_price == 0)
			results_list.push_back(result_dishes); 	//add result_dishes to results_list.
		 //results_list contains list of result_dishes
		
		result_dishes.push_back(dishes_list[i]); // add dish to result_dishes
		
		//calling recursively
		findNumbers(dishes_list, target_price - dishes_list[i].second, results_list, result_dishes, i);   
		i++;      //for the next lowest priced dish.
		
		result_dishes.pop_back();
		//backtracking by removing the last price and later adding new value.	
	}
}
//helper function to sort a STL pair based on first element
bool sortByFirst(const pair<string, double> &a, const pair<string, double> &b)  
{
	return (a.first < b.first);
}
//helper function to sort a STL pair based on first element
bool sortBySecond(const pair<string, double> &a, const pair<string, double> &b)   
{
	return (a.second < b.second);
}

//helper function returns true if the first elements are equal else returns false.
bool filterByFirst(pair<string, double> &a, pair<string, double> &b)  
{
	if (a.first == b.first)
	{
		std::cout << endl << "item - " << a.first << " occured more than once in the itemlist. Ignoring this and proceeding" << endl;
		return true;
	}
	return false;
}

vector<vector<pair<string, double> > > combinationDishes(vector<pair<string, double> >& dishes_list, double target_price)
{
	
	// sort input array based on first element
	sort(dishes_list.begin(), dishes_list.end(), sortByFirst);   
	
	// remove duplicates based on First elements
	dishes_list.erase(std::unique(dishes_list.begin(), dishes_list.end(), filterByFirst), dishes_list.end());
	
	// sort input array based on second element
	sort(dishes_list.begin(), dishes_list.end(), sortBySecond);  
	vector<pair<string, double> > result_dishes;   
	
	//stores array of result_dishes
	vector<vector<pair<string, double> > > results_list;   
	findNumbers(dishes_list, target_price, results_list, result_dishes, 0);  

	return results_list;
}

//frequency of dishes in result_dishes calculator and display function
void print_frequencies(std::vector<pair<string,double> > & v)   
{
	if (!v.empty())
	{
		auto prev = v.front();
		std::size_t freq = 1;

		auto out = [&] { std::cout<<setfill(' ') << setprecision(2)<<fixed<<setw(20)<< prev.first << ": " << freq << " * "<< "$"<<prev.second/1000 <<endl; };

		for (std::size_t i = 1; i < v.size(); ++i)
		{
			if (prev.first == v[i].first)
				++freq;
			else
			{
				out();
				prev = v[i];
				freq = 1;
			}
		}
		out();
	}
}
// Driver code
int main(int argc,char * argv[])
{
	
	if (argc < 2)
	{
		cerr << "Please pass the input file as argument" << endl;
		exit(0);
	}
	vector<pair<string, double> > dishes_list;
	ifstream infile;
	std::string input_file(argv[1]);
	infile.open(input_file);
	if (!infile)
	{
		std::cout << "File Not Found" << endl;
		exit(1);
	}
	std::string read_line;
	std::string dish_price_str;
	std::string dish_name;
	double dish_price;

	//reads each line and if the input is correct stores it in the dishes_list
	while (std::getline(infile, read_line))  
	{
		std::istringstream iss(read_line);
		if (!read_line.length() > 0) {
			continue;
		}
		try
		{
			if (!(std::getline(iss, dish_name, ',')))
				continue;

			if (!(iss >> dish_price_str))
				continue;

			dish_price = stof(dish_price_str.substr(1, dish_price_str.length()));
			dishes_list.push_back(make_pair(dish_name,int(round(dish_price *1000)) ));
		}
		catch (...)
		{
			cerr << "Input Error" << endl;
			continue;
		}
	}
	double target_price = dishes_list[0].second;
	
	//erasing first element because first element in dishes_list is target_price.
	dishes_list.erase(dishes_list.begin());   
	int no_of_dishes = dishes_list.size();
	vector<vector<pair<string, double> > > results_list = combinationDishes(dishes_list, target_price);

	// If result is empty, then
	if (results_list.size() == 0)
	{
		std::cout << " There is no combination of dishes that is equal to the target price";
		return 0;
	}

	// Print all combinations stored in res.
	std::cout <<endl<< setfill(' ') << setprecision(2) << fixed << setw(20) << "Target Price - " << "$" << target_price /1000 <<endl;
	std::cout << setfill('-') << setw(80) << "-" << endl;
	
	//displays each possible outcome in each iteration.
	for (int count_no = 0; count_no < results_list.size(); count_no++)   
	{
		if (results_list[count_no].size() > 0)
		{
			std::cout <<endl<< "Item-List - " << count_no <<endl << endl;
			print_frequencies(results_list[count_no]);
			std::cout << setfill('-') << setw(80) <<"-"<< endl;
		}
	}
	infile.close();
	cout << endl << "Enter any character to exit"<<endl;
	char c;
	std::cin >> c;
	return 0;
}
