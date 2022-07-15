#include<iostream>
#include<random>
#include<chrono>
#include<cmath>
#include <fstream>

using namespace std;

vector<int> Selection_sort(vector<int> vec){
    for(int i = 0; i < vec.size(); i++){
        int min_int = i;
        for(int j = i; j < vec.size(); j++){
            if(vec[j] < vec[min_int]){
                min_int = j;
            }
        }
        int temp = vec[i];
        vec[i] = vec[min_int];
        vec[min_int] = temp;
    }

    return vec;
}

vector<int> Bubble_sort(vector<int> vec){
    for(int i = vec.size()-1; i > -1; i--){
        for(int j = 0; j < i; j++){
            if(vec[j]>vec[j+1]){
                int temp = vec[j];
                vec[j] = vec[j+1];
                vec[j+1] = temp;  
            }
        }
    }
    return vec;
}

vector<int> Bubble_sort_escape(vector<int> vec){
    int i = vec.size()-1;
    bool sorted = true;
    while(i > -1 && sorted){
        bool swapped = false;
        for(int j = 0; j < i; j++){
            if(vec[j]>vec[j+1]){
                int temp = vec[j];
                vec[j] = vec[j+1];
                vec[j+1] = temp; 
                swapped = true; 
            }
        }
        if(!swapped){
            sorted = false;
        }
        else{
            i = i - 1;
        }
    }
    return vec;
}

vector<int> Insertion_sort(vector<int> vec)
{	
	for(int i = 1; i < vec.size(); i++){
		int x = vec[i];
		int j = i-1;
		while(j > -1 && vec[j] > x){
			vec[j+1] = vec[j];
			j = j-1;
			vec[j+1] = x;
		}
	}
	return vec;

}

vector<int> MergeSort(vector<int> vec, vector<int> temp, int left, int right)
{
	if(right - left > 0)
	{
		int mid = floor((left + right)/2);
		vec = MergeSort(vec, temp, left, mid);
		vec = MergeSort(vec, temp, mid+1, right);
		
		for(int i = mid; i >= left; i--)
		{
			temp[i] = vec[i];
		}
		for(int j = mid+1; j <= right; j++)
		{
			temp[right+mid+1-j] = vec[j];
		}

		int i = left;
		int j = right;
        for(int k = left; k <= right; k++)
		{
			if(temp[i] < temp[j])
			{
				vec[k] = temp[i];
				i++;
			}
			else
			{
				vec[k] = temp[j];
				j--;
			}
		}
	}
	return vec;    
}

vector<int> QuickSort(vector<int> vec, int left, int right){
    if(right > left){
        int v = vec[right];
        int i = left;
        int j = right;
        while(i < j){
            while(vec[i]<v){
                i++;
            }
            while(j > i && vec[j]>=v){
                j--;
            }
            if(j > i){
                int t = vec[i];
                vec[i] = vec[j];
                vec[j] = t;
            }
            else{
                int t = vec[i];
                vec[i] = vec[right];
                vec[right] = t;
            }
        }
        vec = QuickSort(vec, left, i-1);
        vec = QuickSort(vec,i+1,right);
    }
    return vec;
}

vector<int> random_input(int N){

    vector<int> num;
    for(int i = 0; i<N; i++){
        random_device rand;
        mt19937 gen(rand());
        uniform_int_distribution<> dist(1, 1000000);
        num.push_back(dist(gen));
    }
    return num;
}

void Print(vector<int> vec, string name){
	cout<<name<<endl;
	cout<<vec[0];
	for(int i = 0; i < vec.size(); i++){
		cout<<", "<<vec[i];
	}
	cout<<endl;
}

int main(){
    
    vector<long long> Bubble_sort_times;
    vector<long long> Bubble_sort_esc_times;
    vector<long long> Selection_sort_times;
    vector<long long> Insertion_sort_times;
    vector<long long> Merge_Sort_times;
    vector<long long> Quick_Sort_times;
    vector<int> rand_nums;
    
	int N = 1000;
    long long timeTaken;
    long long Total_time = 0;
    long long ave_time;
    
    rand_nums = random_input(N);

   while(N < 21000){
    rand_nums = random_input(N);
    vector<int> temp(N);
    for(int i = 0; i<5; i++){
        auto start = chrono::high_resolution_clock::now();
        vector<int> sort = Selection_sort(rand_nums);
        auto finish = chrono::high_resolution_clock::now();
        timeTaken = chrono::duration_cast<chrono::nanoseconds>(finish - start).count(); 
        Total_time += timeTaken;
    }
    ave_time = Total_time/5;
    Selection_sort_times.push_back(ave_time);
    Total_time = 0;

    for(int i = 0; i<5; i++){
        auto start = chrono::high_resolution_clock::now();
        vector<int> sort = Bubble_sort(rand_nums); 
        auto finish = chrono::high_resolution_clock::now();
        timeTaken = chrono::duration_cast<chrono::nanoseconds>(finish - start).count(); 
        Total_time += timeTaken;
    }
    ave_time = Total_time/5;
    Bubble_sort_times.push_back(ave_time);
    Total_time = 0;

    for(int i = 0; i<5; i++){
        auto start = chrono::high_resolution_clock::now();
        vector<int> sort = Bubble_sort_escape(rand_nums);   
        auto finish = chrono::high_resolution_clock::now();
        timeTaken = chrono::duration_cast<chrono::nanoseconds>(finish - start).count(); 
        Total_time += timeTaken;
    }
    ave_time = Total_time/5;
    Bubble_sort_esc_times.push_back(ave_time);
    Total_time = 0;

    for(int i = 0; i<5; i++){
        auto start = chrono::high_resolution_clock::now();
        vector<int> sort4 = Insertion_sort(rand_nums);   
        auto finish = chrono::high_resolution_clock::now();
        timeTaken = chrono::duration_cast<chrono::nanoseconds>(finish - start).count(); 
        Total_time += timeTaken;
    }
    ave_time = Total_time/5;
    Insertion_sort_times.push_back(ave_time);
    Total_time = 0;

    for(int i = 0; i<5; i++){
        auto start = chrono::high_resolution_clock::now();
        vector<int> sort3 = MergeSort(rand_nums, temp, 0 , N-1); 
        auto finish = chrono::high_resolution_clock::now();
        timeTaken = chrono::duration_cast<chrono::nanoseconds>(finish - start).count(); 
        Total_time += timeTaken;
    }
    ave_time = Total_time/5;
    Merge_Sort_times.push_back(ave_time);
    Total_time = 0;
	
    for(int i = 0; i<5; i++){
        auto start = chrono::high_resolution_clock::now();
        vector<int> sort5 = QuickSort(rand_nums, 0 , N-1);   
        auto finish = chrono::high_resolution_clock::now();
        timeTaken = chrono::duration_cast<chrono::nanoseconds>(finish - start).count(); 
        Total_time += timeTaken;
    }
    ave_time = Total_time/5;
    Quick_Sort_times.push_back(ave_time);
    Total_time = 0;

    N = N + 1000;
}

ofstream fw("data.txt", std::ofstream::out);

if(fw.is_open())
    {
    fw << Selection_sort_times[0];
    for (int i = 1; i < Selection_sort_times.size(); i++) {
        fw <<","<<Selection_sort_times[i];
    }
    fw << endl;

    fw << Bubble_sort_times[0];
    for (int i = 1; i < Bubble_sort_times.size(); i++) {
        fw <<","<<Bubble_sort_times[i];
    }
    fw << endl;

    fw << Bubble_sort_esc_times[0];
    for (int i = 1; i < Bubble_sort_esc_times.size(); i++) {
        fw <<","<<Bubble_sort_esc_times[i];
    }
    fw << endl;

    fw << Insertion_sort_times[0];
    for (int i = 1; i < Insertion_sort_times.size(); i++) {
        fw <<","<<Insertion_sort_times[i];
    }
    fw << endl;

    fw << Merge_Sort_times[0];
    for (int i = 1; i < Merge_Sort_times.size(); i++) {
        fw <<","<<Merge_Sort_times[i];
    }
    fw << endl;

    fw << Quick_Sort_times[0];
    for (int i = 1; i < Quick_Sort_times.size(); i++) {
        fw <<","<<Quick_Sort_times[i];
    }
    fw << endl;
    fw.close();
}
else{ 
    cout << "Problem with opening file";
}

return 0;
}
