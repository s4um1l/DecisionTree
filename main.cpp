#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string.h>
#include <cmath>
#include <limits.h>
#include <set>
#include <stdlib.h>
using namespace std;
/*
                                            Decision Tree Program

INPUT: requires two command line arguments  first being the training set  second testing set (data is supposed to clean and with no blank lines)
OUTPUT:tree and classification result on self and test case
Class and Method description:
 class ReadFromFile:
                A basic file handler stores records for future access into a 2D vector named traininglist
                buildRecord() does the above function
                displayList() displays the list
                getUnique() was  just for testing and future use purposes

class Node:
            Basic DS of tree:
             double entropy;
    vector<Node*> children; // vector of childrens
    Node * parent; // parent reference;
    string label; //label node
    string arc_label;//label arc
    int lab; //label node int
    int arc;// lable node
    int attrib_index; // maintains attribute name


 class TreeClassID3:
                creates tree, traverses tree and is used for testing also
                createTree() creates the trees using ID3 algorithm support functions
                            a.validrowchanger() changes the sample size;
                            b.frequency() returns the freq;
                            c.entropy() calculates the entorpy for sample size;
                            d.gain() calculates gain for sample;
                            e.startTree() initializer
                traverseTree(): A DFS order printing of tree
                test():
                        Test wrapper for resucrsive testing of tree
                treetest():
                        recursive finding what is the right classification






*/
void printUsedArray(bool used1,bool used2,bool used3,bool used4,bool used5,bool used6)
{
    //This function was written for test purposes only
    // cout<<"USED ARRAY ON IT WAY"<<endl;
//cout<<used1<<used2<<used3<<used4<<used5<<used6;
}
//Filehandler for the ID 3
class ReadFromFile
{


public:
    vector< vector <int> > trainingList;// To hold the whole list of input data .Actually this is table on which we will operate

    vector <int> record;// A single file record

    // set <int> a1,a2,a3,a4,a5,a6,a7;// Hold unique value of each attribute also class label
    vector<int> no_of_values;
    set <int> a8[7];// Hold unique value of each attribute also class label
    ReadFromFile()
    {
        //initialization of unique values
        for(int i=0; i<7; i++)
            no_of_values.push_back(0);
    }
    void buildRecord(char * path)
    {
        string line;
        ifstream fp (path);
        if (!fp.is_open()) //
            cout<< "Error in the file path";
        else
        {
            getline(fp,line);

            istringstream iss(line);
            string token;
            int i=0,j=0;
            no_of_values[6]=2;// Last column is for class label which in our case is 2 as binary classification
            while(iss >> token)
            {
                if (j%2!=0)
                {
                    istringstream(token)>>no_of_values[i]; // parsing the first row to get unique values of each type
                    // cout<<"Value check at "<<i<<"  "<< no_of_values[i]<<endl;
                    i++;
                }
                j++;
            }
            while (!fp.eof())
            {

                getline(fp,line);
                if (line == "") continue;
                istringstream iss(line);
                string token;
                int count=0;
                while (iss>>token)
                {
                    if (count%7==0)
                        count=0;
                    // cout<<count<<"counter"<<endl;
                    int temp;
                    istringstream(token)>>temp;
                    record.push_back(temp);
                    a8[count++].insert(temp);
                }
                trainingList.push_back(record);
                record.clear();

            }
        }


    }

    //function to display list of data stored
    void displayList()
    {
        vector<vector <int> >::iterator iter=trainingList.begin();
        vector <int> ::iterator iter1;
        cout << "size of the list" << trainingList.size();
        while (iter != trainingList.end())
        {
            //  cout<<"New Record"<<endl;
            for(iter1=(*iter).begin(); iter1!=(*iter).end(); iter1++)
            {
                cout <<*iter1<<endl;
            }
            iter++;
        }


    }

//        bool operator<(int a)
//    {
//        if (*this<a)
//    return 1;
//    else
//    return 0;
//        }
    void getUnique()
    {
        // cout<<"The unique effect"<<a8[6].size();

//         vector<vector <int> >::iterator iter=trainingList.begin();
//         vector <int> ::iterator iter1;
//            while (iter != trainingList.end())
//        {
//          //  cout<<"New Record"<<endl;
//            iter1=(*iter).begin();
//            cout<<"Iter on display"<<*iter1;
//            a1.insert(*(iter1++));
//            a2.insert(*(iter1++));
//            a3.insert(*(iter1++));
//            a4.insert(*(iter1++));
//            a5.insert(*(iter1++));
//            a6.insert(*(iter1++));
//            a7.insert(*(iter1++));
//
//            iter++;
//
//        }
    }
};

//Node
class Node
{
public:
    double entropy;
    vector<Node*> children; // vecotr of children
    Node * parent; // parent reference;
    string label; //label nobel
    string arc_label;
    int lab; //label nobel
    int arc;
    int attrib_index; // maintains attribute name

};

//Tree functionality
class TreeClassID3
{

    Node * root;
    vector<int> subtable;
public:
    TreeClassID3 ()
    {
        root=NULL;
    }
    Node * createTree(set <int> category,vector <int> trainingrows,ReadFromFile input,int level,bool used1,bool used2,bool used3,bool used4,bool used5,bool used6);
    double entropyCalculator(vector <int> valid_rows,ReadFromFile input);
    double Gain(int attrib_index,set <int> category,ReadFromFile input,vector <int> valid_rows,bool used1,bool used2,bool used3,bool used4,bool used5,bool used6);
    void validrowchanger(int attrib_index,set <int> category,ReadFromFile input,vector <int> valid_rows,int attrib_value,bool used1,bool used2,bool used3,bool used4,bool used5,bool used6);
    double frequency(int attrib_value,ReadFromFile input,vector<int> valid_rows,int attrib_index);
    void startTree(ReadFromFile input);
    void traverseTree(Node * trav,int level,int child);
    void test(ReadFromFile input);
    bool treetest(Node * in,vector<int> input);
//    set<int> returnSet(int attrib_index,ReadFromFile input){
//    if (attrib_index==0)return input.a1;
//    if (attrib_index==1)return input.a2;
//    if (attrib_index==2)return input.a3;
//    if (attrib_index==3)return input.a4;
//    if (attrib_index==4)return input.a5;
//    if (attrib_index==5)return input.a6;
//    }
    int checkused(bool used1,bool used2,bool used3,bool used4,bool used5,bool used6)
    {

        if (used1==0||used2==0||used3==0||used4==0||used5==0||used6==0)
            return 1;
        else
            return 0;
    }

};
bool TreeClassID3::treetest(Node * in,vector<int> input)
{
    bool a;
    if (in->children.size()==0)
    {
        return in->lab;
    }
    for (int i=0; i<in->children.size(); i++)
    {
        if (in->children[i]->arc==input[in->attrib_index])
        {
            a= treetest(in->children[i],input);
        }
    }
    return a;
}

void TreeClassID3::test(ReadFromFile input)
{
    int no_of_ones=0;
    int no_of_zeroes=0;
    for (int i=0; i<input.trainingList.size(); i++)
    {

        bool a=treetest(root,input.trainingList[i]);
        // cout <<"result is "<<a<<endl;
        if (a==input.trainingList[i][6])
            no_of_ones++;
        else
            no_of_zeroes++;


    }
    double result= (double)no_of_ones/(double)(no_of_ones+no_of_zeroes);
    cout<<"-----------------RESULT -------------------"<<endl;
    cout<<"Accuracy of training set (Total of "<<no_of_ones+no_of_zeroes<<" Instances) "<< result*100<<endl;
}

double TreeClassID3::Gain(int attrib_index,set <int> category,ReadFromFile input,vector <int> valid_rows,bool used1,bool used2,bool used3,bool used4,bool used5,bool used6)
{
    double gain=0;
    set<int>::iterator it1;

    for (it1=input.a8[attrib_index].begin(); it1!=input.a8[attrib_index].end(); it1++)
    {
        subtable = valid_rows;
        validrowchanger(attrib_index,category,input,valid_rows,*it1,used1,used2,used3,used4,used5,used6);
        double a=frequency(*it1,input,valid_rows,attrib_index);
        double b=entropyCalculator(subtable,input);
        gain+= a*b ;

    }
    return gain;
}


double TreeClassID3::frequency(int attrib_value,ReadFromFile input,vector<int> valid_rows,int attrib_index)
{
    int no_of_valid=0;
    int no_of_value=0;
    for (int i=0; i<input.trainingList.size(); i++)
    {
        if (valid_rows[i]==1)
        {
            no_of_valid++;
            if (input.trainingList[i][attrib_index]==attrib_value)
                no_of_value++;
        }
    }
    double freq;
    if (no_of_valid==0)
        freq=0;
    else
        freq= (double)no_of_value/(double)no_of_valid;
// cout<<"Freq of "<< attrib_value<< "at index"<<attrib_index<<"is "<<freq<<endl;
    return freq;
}


void  TreeClassID3::validrowchanger(int attrib_index,set <int> category,ReadFromFile input,vector <int> valid_rows,int attrib_value,bool used1,bool used2,bool used3,bool used4,bool used5,bool used6)
{

    for (int i=0; i<input.trainingList.size(); i++)
    {
        if (valid_rows[i]==1)
        {
            if (input.trainingList[i][attrib_index]==attrib_value)
                subtable[i]=1;
            else
                subtable[i]=0;
        }
        else
            subtable[i]=0;
    }
    printUsedArray(used1,used2,used3,used4,used5,used6);

}
void TreeClassID3::startTree(ReadFromFile input)
{

    vector<int> trainingrows(input.trainingList.size(),1);//all rows are part of study
//    for (int i=0;i<6;i++)
//    used_array[i]=0; //all array values are unsued initially represents feature vectors

    bool used1=0;
    bool used2=0;
    bool used3=0;
    bool used4=0;
    bool used5=0;
    bool used6=0;
    //cout<<"Starting Array"<<endl;
    // printUsedArray(used1,used2,used3,used4,used5,used6);
    root=createTree(input.a8[6],trainingrows,input,0,used1,used2,used3,used4,used5,used6);
    cout<< "------------------------Part A ------------------------------ "<<endl;
    traverseTree(root,1,0);

}
void TreeClassID3::traverseTree(Node * trav,int level,int child)
{
    if (trav==NULL)
        return;
    if (trav->children.size()==0)
    {
        cout<<":"<<trav->label<<endl;
        return;
    }
    else
    {


        for (int i =0 ; i<trav->children.size(); i++)
        {
            for (int j=0; j<level-1; j++)
                cout<<"| ";
            cout<<(trav->label)<<"=";

            if (trav->children[i]->children.size()==0)
                cout<<trav->children[i]->arc_label;
            else
            {

                cout<<trav->children[i]->arc_label<<endl;


            }
            traverseTree(trav->children[i],level+1,i);
        }
    }

}

//function for entropy calculation passed is subtable for calculation
double TreeClassID3::entropyCalculator(vector <int> valid_rows,ReadFromFile input)
{
    int number_of_ones=0;   //valid in this case as we have two unique values only
    int number_of_zeroes=0;
    int sum=0;
    double entropy=0,temp=0,temp1=0;
    for (int i=0; i<input.trainingList.size(); i++)
    {
        if (valid_rows[i]==1)
        {
            if (input.trainingList[i][6]==1)
                number_of_ones++;
            else
                number_of_zeroes++;
        }
    }

    sum=number_of_ones+number_of_zeroes;
    //  cout<<"The entropy sum is "<<sum;
    if (sum)
    {
        temp=(double)number_of_ones/sum;
        temp1=(double)number_of_zeroes/sum;
    }
    else
    {
        temp=0;
        temp1=0;
    }
    //cout<< "temp "<<temp;
    if (temp==0 && temp1==0)
        entropy = 0;
    else if (temp==0)
    {
        entropy=  - (temp1*(log2(temp1)));
    }
    else if (temp1==0)
        entropy= ((-1)*temp*(log2(temp)));
    else
        entropy= ((-1)*temp*(log2(temp))) - (temp1*(log2(temp1)));
    // cout << "New Entropy  " << entropy<<endl;
    return entropy;

}


//build tree reursively
Node* TreeClassID3::createTree(set <int> category,vector <int> trainingrows,ReadFromFile input,int level,bool used1,bool used2,bool used3,bool used4,bool used5,bool used6)
{

    if (trainingrows.size()==0)
    {
        cout<<"trainng size 0"; //base case 1
        return NULL;
    }
    Node * temp = new Node();

    set <int> uniquelabels;
    ostringstream convert;
    convert<<level;
    string pathout =convert.str();
    int in=0;
    ofstream fp1(pathout.c_str());
    for (int i=0; i<input.trainingList.size(); i++)
    {

        //cout<<"training list"<<trainingList.size()<<"I am at "<<i<<endl;
        if (trainingrows[i]==1)
        {
            uniquelabels.insert(input.trainingList[i][6]);
            fp1<<input.trainingList[i][0]<<input.trainingList[i][1]<<input.trainingList[i][2]<<input.trainingList[i][3]<<input.trainingList[i][4]<<input.trainingList[i][5]<<input.trainingList[i][6]<<endl;

        }
    }

//for (vector <vector <int> >::iterator  ita=trainingList.begin();ita!=trainingList.end();ita++)
//{
//    if (trainingrows[in++]==1){
//    vector<int>::iterator lastenemy= (*ita).end();
//     uniquelabels.insert((*lastenemy));
//    }
//}
//cout<<endl<< uniquelabels.size()<<"the size of earth"<<endl;
    double ent=entropyCalculator(trainingrows,input);
    if (checkused(used1,used2,used3,used4,used5,used6)==0)
    {
        int sum=0;
        for (int i=0; i<trainingrows.size(); i++)
            sum+=trainingrows[i];
        if (sum==0)             //Table empty base csae 2
        {
            //   cout<<"Table becomes empty"<<endl;
            return NULL;
        }
        else
        {
            //     cout<<"Used all attributes"<<endl;           //none of predictive attribute available so we label with most common value
            int no_of_zeros=0,no_of_ones=0;
            for (int i=0; i<input.trainingList.size(); i++)
            {
                if (trainingrows[i]==1)
                {

                    if (input.trainingList[i][6]==*category.begin())
                        no_of_zeros++;
                    else
                        no_of_ones++;
                }
            }
            if (no_of_zeros>no_of_ones)
            {
//     convert<<*category.begin();
//string lb =convert.str();
//cout << "The master of categories    -------------------------"<<endl;
//cout<<"new one "<<*category.begin();
//cout<<"temp out of attribute label"<<lb<<endl;
                temp->label="0" ;
                temp->lab=0;
                return temp;
            }
            else
            {
//   convert<<*(--category.end());
//string lb =convert.str();
//cout<<"temp out of attribute label"<<lb<<endl;
                temp->label="1" ;
                temp->lab=1;
                return temp;
            }
        }
    }
    else if (uniquelabels.size()==1)             //values of one category only we return a node lableled with that category
    {
//cout<<"Finally Classified"<<endl;
        set <int>::iterator unlabel = uniquelabels.begin();
        stringstream ss;

        ss<< *unlabel;
        string lb =ss.str();
        temp->label=lb;
        temp->lab=*unlabel;
        return temp;
    }
    else
    {
//cout<<"else welse";
        double min=1000;
        int pos=0;
//cout<<"clean for gaiins---------------------------"<<endl;
        for (int i=0; i<6; i++)
        {
            if (i==0)
            {
                if (used1==1)
                    continue;
            }
            if (i==1)
            {
                if (used2==1)
                    continue;
            }
            if (i==2)
            {
                if (used3==1)
                    continue;
            }
            if (i==3)
            {
                if (used4==1)
                    continue;
            }
            if (i==4)
            {
                if (used5==1)
                    continue;
            }
            if (i==5)
            {
                if (used6==1)
                    continue;
            }
            double gain =Gain(i,category,input,trainingrows,used1,used2,used3,used4,used5,used6);
            //cout<<"new gain at attribute"<<i<< "is "<<gain;
            if (min>gain)
            {
//cout<<"Gains change "<< ent-gain<<endl;
                min=gain;
                pos=i;
            }
        }
//cout<< "Minimum gain at"<<pos<<"value "<<min<<"end"<<endl;
        double ent1=entropyCalculator(trainingrows,input);
        double percentcheck = abs(ent1-min)/ent1*100;

        if (percentcheck<0.0000001)
        {
//cout<<"PercentCHeck present rule outs "<<percentcheck;
            int no_of_zeros=0,no_of_ones=0;
            for (int i=0; i<input.trainingList.size(); i++)
            {
                if (trainingrows[i]==1)
                {

                    if (input.trainingList[i][6]==*category.begin())
                        no_of_zeros++;
                    else
                        no_of_ones++;
                }
            }
            if (no_of_zeros>no_of_ones)
            {
                stringstream ss;
                ss<<*category.begin();
                string lb =ss.str();

                temp->label=lb ;
                temp->lab=*category.begin();
                return temp;
            }
            else
            {
                stringstream ss;
                ss<<*(--category.end());
                temp->lab=*category.end();
                string lb =ss.str();

                temp->label=lb ;
                return temp;
            }



        }
        else
        {
            stringstream ss;
            ss<<(pos+1);
            string lb =ss.str();
            temp->lab=pos+1;
            temp->label=lb ;
            temp->attrib_index=pos;
            set<int> minimum= input.a8[pos];
            if (pos==0)used1=1;
            if (pos==1)used2=1;
            if (pos==2)used3=1;
            if (pos==3)used4=1;
            if (pos==4)used5=1;
            if (pos==5)used6=1;
            for (set<int>::iterator iter=minimum.begin(); iter!=minimum.end(); iter++)
            {
//  cout<<endl<<"The new attribute for which value be calculated"<<*iter<<"at pos"<<pos<<"total count"<<minimum.size()<<endl;
                subtable=trainingrows;
                for (int i=0; i<input.trainingList.size(); i++)
                {
                    subtable[i]=0;
                }

                validrowchanger(pos,category,input,trainingrows,*iter,used1,used2,used3,used4,used5,used6);

                Node * N1=createTree(category,subtable,input,level+1,used1,used2,used3,used4,used5,used6);
//cout<<"level="<<level<<endl;
                if (N1!=NULL)
                {
                    N1->parent=temp;
                    N1->arc=*iter;
                    temp->children.push_back(N1);
                    stringstream ss;
                    ss<<(*iter);

                    string lb =ss.str();
                    // cout<<"arc label stored "<<lb<<endl;
                    N1->arc_label=lb;
                }
            }
//int n;
//cin>>n;


        }
    }
    return temp;

}



int main(int argc, char* argv[])
{
    //cout<<argv[1];
    ReadFromFile train,test;  // object train for handling records related to training  ,similarly test with testing
    TreeClassID3 id3;
    train.buildRecord(argv[1]);
    train.getUnique();
    //  cout<<"training list"<<trainingList.size()<<"great size"<<endl;
    //train.displayList();
    cout<< endl<<"------------------------Welcome to HomeWork 1 Decision Tree---------------------"<<endl;
    test.buildRecord(argv[2]);
    id3.startTree(train);
    cout<< endl<<"------------------------Part B------------------------------ "<<endl;
    id3.test(train);
    cout<< endl<<"------------------------Part C------------------------------ "<<endl;
    id3.test(test);
    //cout<<"The powerful testing tree"<<test.trainingList.size();
    //test.displayList();
    //test.getUnique();
    //train.displayList();


    return 0;
}
