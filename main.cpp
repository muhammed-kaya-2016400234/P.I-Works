/*

Run the code with:
 $ g++ main.cpp -o main -std=c++11
 $ main path/to/input/file


*/
#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <sstream>
#include <math.h>
#include <algorithm>
using namespace std;

bool isPrime(int a);
vector<vector<int>> den(vector<int> a,vector<int> level,int index,int maximumLevel);


int main(int argc,char * argv[]) {

    vector<int> a;
    ifstream file;
    file.open(argv[1]);
    string b;
    int counter=0;
    int level=0;
    string line;
    vector<int> levels;

    //folloiwng while loop reads input file and stores numbers in array "a"
    while(getline(file,line)){
    level++;
        vector<string> tokens;
        istringstream iss(line);
        copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(tokens));
        for(auto it=tokens.begin();it!=tokens.end();it++){
            int t=stoi(*it);
            a.push_back(t);
            counter++;
            levels.push_back(level);

        }
    }

    //vector r stores all possible paths in the pyramid
    vector<vector<int>> r=den(a,levels,0,level);


/*
    //prints all possible paths

   for(auto it=r.begin();it!=r.end();it++){
           for(auto i=it->begin();i!=it->end();i++){
               cout<<*i<<" ";

           }
           cout<<endl;
       }
  */



    //following loop finds the length of the path that is closest to ground of the pyramid
    int maxDepth=0;
    for(auto it=r.begin();it!=r.end();it++) {
        int depth=it->size();
        if(depth>maxDepth)
            maxDepth=depth;

    }

    int max=0;          //stores the maximum sum
    int indexofMax=0;     //stores the index of the path that supplies the maximum sum
    int i=0;

    //In following loop ,we find the maximum of the sums
    for(auto it=r.begin();it!=r.end();it++){
        int sum=0;

        //consider only the paths that are closest to the ground of pyramid
        //Rule 4.:You have to reach at the end of the pyramid as much as possible.
        if(it->size()==maxDepth) {
            for (auto iter = it->begin(); iter != it->end(); iter++) {
                sum += a[*iter];

            }

            if (sum > max ) {
                indexofMax = i;
                max = sum;

            }
        }

        i++;

    }


    vector<int> maxPath=r[indexofMax];
    reverse(maxPath.begin(),maxPath.end());
    cout<<"Path is : ";
    for(int i=0;i<maxPath.size();i++)
        cout<<a[maxPath[i]]<<" ";
    cout<<endl;
    cout<<"Maximum sum is "<<max<<endl;




    return 0;
}

//returns true if parameter a is prime number
bool isPrime(int a){
    if(a==1) return false;
    for(int i=2;i<=sqrt(a);i++){
        if(a%i==0)
            return false;
    }
    return true;
}

//this function is a recursive function.It finds out all possible paths branching from a number to the ground
//of the pyramid
vector<vector<int>> den(vector<int> a,vector<int> level,int index,int maximumLevel){


    vector<vector<int>> path;

    if(isPrime(a[index])){

        return path;
    }

    if(level[index]!=maximumLevel) {


            path=den(a, level, index + level[index],maximumLevel);


            vector<vector<int>> path2;
            path2 = den(a, level, index + level[index] + 1, maximumLevel);



            if(path.empty()&&!path2.empty()) {
               path=path2;
            }
            else if(path.empty()&&path2.empty()){
                vector<int> f;
                f.push_back(index);
                path.push_back(f);
                return path;

            }

            else {

                for (auto it = path2.begin(); it != path2.end(); it++) {
                    path.push_back(*it);

                }


            }


            for (auto it = path.begin(); it != path.end(); it++) {
                it->push_back(index);
            }


    }
    else{
        vector<int> f;
        f.push_back(index);
        path.push_back(f);
    }

return path;
}

