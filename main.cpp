#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string.h>
#include <cmath>
#include <set>
#define FEATURES 7 // no of columns in features in  vector alongwith class labels

using namespace std;
set <int> a1,a2,a3,a4,a5,a6;
vector <int> record;// A single file record
vector< vector <int> > trainingList(0,record);// To hold the whole list of input data .
vector<int> no_of_values(7,0); // Hold unique value of each attribute also class label
class ReadFromFile
{


public:
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
                istringstream iss(line);
                string token;
                while (iss>>token)
                {
                    int temp;
                    istringstream(token)>>temp;
                    record.push_back(temp);
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
        while (iter != trainingList.end())
        {
            cout<<"New Record"<<endl;
            for(iter1=(*iter).begin(); iter1!=(*iter).end(); iter1++)
            {
                cout <<*iter1<<endl;
            }
            iter++;
        }


    }
    void getUnique()
    {
        for (int i=0; i<trainingList.size(); i++)
        {
            a1.insert(trainingList[i][0]);
            a2.insert(trainingList[i][1]);
            a3.insert(trainingList[i][2]);
            a4.insert(trainingList[i][3]);
            a5.insert(trainingList[i][4]);
            a6.insert(trainingList[i][5]);
        }
        cout<<"The great count is "<<a1.size()<<endl;
        set<int>::iterator it;
        for (it=a1.begin(); it!=a1.end(); it++)
            cout<<*it;
    }




};
// to store node information
class Node
{
public:
    double entropy;
    vector<Node*> children; // vecotr of children
    Node * parent; // parent reference;
    int attrib_index;

};
//to store Tree information
class TreeClass
{
    Node *root; //start root
    int* valid_rows;
    int* valid_rows_clone;
    int* valid_rows_clone1;
    int* valid_rows_clone2;
    int* valid_rows_clone3;
    int* valid_rows_clone5;
    int* valid_rows_clone6;
    int* valid_rows_clone4;
    set<int>::iterator it;
    bool used_array[6];
public:
    TreeClass()
    {
        root==NULL;
    }
    void buildTree();
    void initialValidator(); // function to initiate initial values of Validator and Used_array
    double entropyCalculator();
    double entropyCalculator(int attr_index,int attr_value);
    void buildTreeRecursively(double entropy,int attrib_index,Node *parent,bool used_array[],int valid_rows[]);//have t owrite some parameters
    //Node processTree(int attrib_index,int attrib_value);
    void validateModifier(int attrib_index,int attrib_value,int valid_rows[]);
    int maxGain(double S,int numberofS,bool used_array[],int valid_rows[]);
    int countValue(int attr_index,int attr_value);
    int checkused(bool used_array[]){
    for (int i=0;i<6;i++){
    if (used_array[i]==0)
    return 1;
    }
    return 0;
    }
};

void TreeClass::validateModifier(int attrib_index,int attrib_value,int valid_rows[])
{

    for (int i=0; i<trainingList.size(); i++)
    {
        if (valid_rows[i]==1)
        {
            valid_rows[i]=0;
            if (trainingList[i][attrib_index]==attrib_value)
            {
                valid_rows[i]=1;
            }
        }
    }

}

void TreeClass::buildTreeRecursively(double entropy,int attrib_index,Node *parent,bool used_array[],int valid_rows[])
{

    if (entropy ==0)
    {

        return ;
    }

     if (attrib_index==0){
              for (set<int>::iterator it2=a1.begin(); it2!=a1.end(); it2++)
             {
              int a=*it2;
            validateModifier(attrib_index,*it2,valid_rows);
            int sum=0;
            double s=entropyCalculator(attrib_index,*it2);
         //   cout << "Entropy of recursive node"<<s;
            for (int i=0; i<trainingList.size(); i++)
            {
                if (valid_rows[i]==1)
                {
                    sum++;
                }
            }
        //    cout<< "The final sum for value "<<*it2<<"comes out ot be " <<sum<<endl;
            int sam=0,sam1=0;
//            for (int t=0; t<trainingList.size(); t++)
//            {
//                if (valid_rows[t]==1)
//                    sam++;
//                if (valid_rows_clone[t]==1)
//                    sam1++;
//
//            }
//            cout<<"the comparision function"<<sam<<"and the orginial clone "<<sam1<<endl;
            // cout<< "Max gain at "<< maxGain(s,sum);
            for(int k=0; k<trainingList.size(); k++)
                valid_rows_clone6[k]=valid_rows_clone[k];

            if (checkused(used_array)==0)
            return;
            int max1=maxGain(s,sum,used_array,valid_rows);
            cout <<"new max"<<max1;
            used_array[max1]=1;

           buildTreeRecursively(s,max1,root,used_array,valid_rows);
            cout<<"time for me to return";
            used_array[max1]=0;
            //cout<<"Reaching";
            for(int k=0; k<trainingList.size(); k++)
                valid_rows_clone[k]=valid_rows_clone6[k];
            for(int k=0; k<trainingList.size(); k++)
                valid_rows[k]=valid_rows_clone[k];

        }
         }
     if (attrib_index==1){
            for (set<int>::iterator it2=a2.begin(); it2!=a2.end(); it2++)
             {
              int a=*it2;
            validateModifier(attrib_index,*it2,valid_rows);
            int sum=0;
            double s=entropyCalculator(attrib_index,*it2);
       //     cout << "Entropy of recursive node"<<s;
            for (int i=0; i<trainingList.size(); i++)
            {
                if (valid_rows[i]==1)
                {
                    sum++;
                }
            }
      //      cout<< "The final sum for value "<<*it2<<"comes out ot be " <<sum<<endl;
            int sam=0,sam1=0;
//            for (int t=0; t<trainingList.size(); t++)
//            {
//                if (valid_rows[t]==1)
//                    sam++;
//                if (valid_rows_clone[t]==1)
//                    sam1++;
//
//            }
//            cout<<"the comparision function"<<sam<<"and the orginial clone "<<sam1<<endl;
            // cout<< "Max gain at "<< maxGain(s,sum);
            for(int k=0; k<trainingList.size(); k++)
                valid_rows_clone1[k]=valid_rows_clone[k];

            int max1=maxGain(s,sum,used_array,valid_rows);
            cout <<"new max"<<max1;
            used_array[max1]=1;

           buildTreeRecursively(s,max1,root,used_array,valid_rows);
            cout<<"time for me to return";
            used_array[max1]=0;
            //cout<<"Reaching";
            for(int k=0; k<trainingList.size(); k++)
                valid_rows_clone[k]=valid_rows_clone1[k];
            for(int k=0; k<trainingList.size(); k++)
                valid_rows[k]=valid_rows_clone[k];

        }
         }
     if (attrib_index==2){
              for (set<int>::iterator it2=a3.begin(); it2!=a3.end(); it2++)
             {
              int a=*it2;
            validateModifier(attrib_index,*it2,valid_rows);
            int sum=0;
            double s=entropyCalculator(attrib_index,*it2);
     //       cout << "Entropy of recursive node"<<s;
            for (int i=0; i<trainingList.size(); i++)
            {
                if (valid_rows[i]==1)
                {
                    sum++;
                }
            }
   //         cout<< "The final sum for value "<<*it2<<"comes out ot be " <<sum<<endl;
            int sam=0,sam1=0;
//            for (int t=0; t<trainingList.size(); t++)
//            {
//                if (valid_rows[t]==1)
//                    sam++;
//                if (valid_rows_clone[t]==1)
//                    sam1++;
//
//            }
//            cout<<"the comparision function"<<sam<<"and the orginial clone "<<sam1<<endl;
            // cout<< "Max gain at "<< maxGain(s,sum);
            for(int k=0; k<trainingList.size(); k++)
                valid_rows_clone2[k]=valid_rows_clone[k];

            int max1=maxGain(s,sum,used_array,valid_rows);
            cout <<"new max"<<max1;
            used_array[max1]=1;

           buildTreeRecursively(s,max1,root,used_array,valid_rows);
            cout<<"time for me to return";
            used_array[max1]=0;
            //cout<<"Reaching";
            for(int k=0; k<trainingList.size(); k++)
                valid_rows_clone[k]=valid_rows_clone2[k];
            for(int k=0; k<trainingList.size(); k++)
                valid_rows[k]=valid_rows_clone[k];

        }
         }
     if (attrib_index==3){
         for (set<int>::iterator it2=a4.begin(); it2!=a4.end(); it2++)
             {
              int a=*it2;
            validateModifier(attrib_index,*it2,valid_rows);
            int sum=0;
            double s=entropyCalculator(attrib_index,*it2);
     //       cout << "Entropy of recursive node"<<s;
            for (int i=0; i<trainingList.size(); i++)
            {
                if (valid_rows[i]==1)
                {
                    sum++;
                }
            }
   //         cout<< "The final sum for value "<<*it2<<"comes out ot be " <<sum<<endl;
            int sam=0,sam1=0;
//            for (int t=0; t<trainingList.size(); t++)
//            {
//                if (valid_rows[t]==1)
//                    sam++;
//                if (valid_rows_clone[t]==1)
//                    sam1++;
//
//            }
//            cout<<"the comparision function"<<sam<<"and the orginial clone "<<sam1<<endl;
            // cout<< "Max gain at "<< maxGain(s,sum);
            for(int k=0; k<trainingList.size(); k++)
                valid_rows_clone3[k]=valid_rows_clone[k];

            int max1=maxGain(s,sum,used_array,valid_rows);
            cout <<"new max"<<max1;
            used_array[max1]=1;

           buildTreeRecursively(s,max1,root,used_array,valid_rows);
            cout<<"time for me to return";
            used_array[max1]=0;
            //cout<<"Reaching";
            for(int k=0; k<trainingList.size(); k++)
                valid_rows_clone[k]=valid_rows_clone3[k];
            for(int k=0; k<trainingList.size(); k++)
                valid_rows[k]=valid_rows_clone[k];

        }
     }
    if (attrib_index==4)
    {
        cout<<a5.size();

        for (set<int>::iterator it2=a5.begin(); it2!=a5.end(); it2++)
        {
            int a=*it2;
            validateModifier(attrib_index,*it2,valid_rows);
            int sum=0;
            double s=entropyCalculator(attrib_index,*it2);
       //     cout << "Entropy of recursive node"<<s;
            for (int i=0; i<trainingList.size(); i++)
            {
                if (valid_rows[i]==1)
                {
                    sum++;
                }
            }
       //     cout<< "The final sum for value "<<*it2<<"comes out ot be " <<sum<<endl;
            int sam=0,sam1=0;
//            for (int t=0; t<trainingList.size(); t++)
//            {
//                if (valid_rows[t]==1)
//                    sam++;
//                if (valid_rows_clone[t]==1)
//                    sam1++;
//
//            }
//            cout<<"the comparision function"<<sam<<"and the orginial clone "<<sam1<<endl;
            // cout<< "Max gain at "<< maxGain(s,sum);
            for(int k=0; k<trainingList.size(); k++)
                valid_rows_clone4[k]=valid_rows_clone[k];

            int max1=maxGain(s,sum,used_array,valid_rows);
            cout <<"new max"<<max1;
            used_array[max1]=1;

           buildTreeRecursively(s,max1,root,used_array,valid_rows);
            cout<<"time for me to return";
            used_array[max1]=0;
            //cout<<"Reaching";
            for(int k=0; k<trainingList.size(); k++)
                valid_rows_clone[k]=valid_rows_clone4[k];
            for(int k=0; k<trainingList.size(); k++)
                valid_rows[k]=valid_rows_clone[k];

        }

    }
    if (attrib_index==5){

        for (set<int>::iterator it2=a6.begin(); it2!=a6.end(); it2++)
            {
         int a=*it2;
            validateModifier(attrib_index,*it2,valid_rows);
            int sum=0;
            double s=entropyCalculator(attrib_index,*it2);
     //       cout << "Entropy of recursive node"<<s;
            for (int i=0; i<trainingList.size(); i++)
            {
                if (valid_rows[i]==1)
                {
                    sum++;
                }
            }
    //        cout<< "The final sum for value "<<*it2<<"comes out ot be " <<sum<<endl;
            int sam=0,sam1=0;
//            for (int t=0; t<trainingList.size(); t++)
//            {
//                if (valid_rows[t]==1)
//                    sam++;
//                if (valid_rows_clone[t]==1)
//                    sam1++;
//
//            }
//            cout<<"the comparision function"<<sam<<"and the orginial clone "<<sam1<<endl;
            // cout<< "Max gain at "<< maxGain(s,sum);
            for(int k=0; k<trainingList.size(); k++)
                valid_rows_clone5[k]=valid_rows_clone[k];

            int max1=maxGain(s,sum,used_array,valid_rows);
            cout <<"new max"<<max1;
            used_array[max1]=1;

           buildTreeRecursively(s,max1,root,used_array,valid_rows);
            cout<<"time for me to return";
            used_array[max1]=0;
            //cout<<"Reaching";
            for(int k=0; k<trainingList.size(); k++)
                valid_rows_clone[k]=valid_rows_clone5[k];
            for(int k=0; k<trainingList.size(); k++)
                valid_rows[k]=valid_rows_clone[k];

        }
        }



}

double TreeClass::entropyCalculator(int attr_index,int attr_value)
{
    int number_of_ones=0;
    int number_of_zeroes=0;
    int sum=0;
    double entropy=0,temp=0,temp1=0;
    for (int i=0; i<trainingList.size(); i++)
    {
        if (valid_rows[i]==1)
        {
            if (trainingList[i][6]==1)
                number_of_ones++;
            else
                number_of_zeroes++;
        }
    }

    sum=number_of_ones+number_of_zeroes;

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
        entropy=  - (temp1*(log10(temp1)/log10(2)));
    }
    else if (temp1==0)
        entropy= ((-1)*temp*(log10(temp)/log10(2)));
    else
        entropy= ((-1)*temp*(log10(temp)/log10(2))) - (temp1*(log10(temp1)/log10(2)));
    //cout << "New Entropy at attribute  " <<attr_index<<"value"<<attr_value<<"is "<<  entropy<<endl;
    return entropy;



}

int TreeClass::countValue(int attr_index,int attr_value)
{
    int count=0;

    for (int i=0; i<trainingList.size(); i++)
    {
        valid_rows[i]=0;
        if (valid_rows_clone[i]==1)
        {
            //   cout<<"reaching";
            if (trainingList[i][attr_index]==attr_value)
            {
                valid_rows[i]=1;
                count++;
            }
        }
    }
//cout << "Saumil"<<count;
    return count;


}

int TreeClass::maxGain(double S,int numberofS,bool used_array[],int valid_rows[])
{
    int position=0;
    double max=0;
    set<int>::iterator it1;
    double gain;
    for (int i=0; i<6; i++)
    {
        gain=S;
        if (used_array[i]!=1)
        {
            for(int k=0; k<trainingList.size(); k++)
                valid_rows_clone[k]=valid_rows[k];

            if (i==0)
            {
                for (it1=a1.begin(); it1!=a1.end(); it1++)
                {
                    gain-=(((double)countValue(i,*it1)/(double)numberofS)*entropyCalculator(i,*it1)) ;
                    for(int k=0; k<trainingList.size(); k++)
                        valid_rows[k]=valid_rows_clone[k];

                }
            }
            if (i==1)
            {
                for (it1=a2.begin(); it1!=a2.end(); it1++)
                {
                    gain-=(((double)countValue(i,*it1)/(double)numberofS)*entropyCalculator(i,*it1)) ;
                    for(int k=0; k<trainingList.size(); k++)
                        valid_rows[k]=valid_rows_clone[k];
                }
            }

            if (i==2)
            {
                for (it1=a3.begin(); it1!=a3.end(); it1++)
                {
                    gain-=(((double)countValue(i,*it1)/(double)numberofS)*entropyCalculator(i,*it1)) ;
                    for(int k=0; k<trainingList.size(); k++)
                        valid_rows[k]=valid_rows_clone[k];
                }
            }

            if (i==3)
            {
                for (it1=a4.begin(); it1!=a4.end(); it1++)
                {
                    gain-=(((double)countValue(i,*it1)/(double)numberofS)*entropyCalculator(i,*it1)) ;
                    for(int k=0; k<trainingList.size(); k++)
                        valid_rows[k]=valid_rows_clone[k];
                }
            }

            if (i==4)
            {
                for (it1=a5.begin(); it1!=a5.end(); it1++)
                {
                    gain-=(((double)countValue(i,*it1)/(double)numberofS)*entropyCalculator(i,*it1)) ;
                    for(int k=0; k<trainingList.size(); k++)
                        valid_rows[k]=valid_rows_clone[k];
                }
            }

            if (i==5)
            {
                for (it1=a6.begin(); it1!=a6.end(); it1++)
                {
                    gain-=(((double)countValue(i,*it1)/(double)numberofS)*entropyCalculator(i,*it1)) ;
                    for(int k=0; k<trainingList.size(); k++)
                        valid_rows[k]=valid_rows_clone[k];
                }
            }

         //   cout<<"Gain at attribute "<<i<<"is "<<gain<<"old maxima "<<max<<endl;
            if (max < gain)
            {
                //cout<< "Gain Change"<<gain<<endl;
                // cout<< "position"<< i<<endl;
                max=gain;
                position=i;
            }
        }
    }
  //  cout << "maxim gain "<< max<< "at attribute" << position<<endl;
    return position;
}
double TreeClass::entropyCalculator()
{
    int number_of_ones=0;
    int number_of_zeroes=0;
    int sum=0;
    double entropy=0,temp=0,temp1=0;
    for (int i=0; i<trainingList.size(); i++)
    {
        if (valid_rows[i]==1)
        {
            if (trainingList[i][6]==1)
                number_of_ones++;
            else
                number_of_zeroes++;
        }
    }

    sum=number_of_ones+number_of_zeroes;
    temp=(double)number_of_ones/sum;
    temp1=(double)number_of_zeroes/sum;
    //cout<< "temp "<<temp;
    entropy= ((-1)*temp*(log2(temp))) - (temp1*(log2(temp1)));
    return entropy;
}
void TreeClass::buildTree()
{
    valid_rows=new int[trainingList.size()];//change them to constructor
    valid_rows_clone=new int[trainingList.size()];
    valid_rows_clone1=new int[trainingList.size()];
    valid_rows_clone2=new int[trainingList.size()];
    valid_rows_clone3=new int[trainingList.size()];
    valid_rows_clone4=new int[trainingList.size()];
    valid_rows_clone5=new int[trainingList.size()];
    valid_rows_clone6=new int[trainingList.size()];

    initialValidator();
    double ent=entropyCalculator();
    cout << " Entropy is  " << ent<<endl;
    cout<< "list size"<< trainingList.size()<<endl;
    int max=maxGain(ent,trainingList.size(),used_array,valid_rows);
    cout << "Max is "<< max<<endl;
    Node *temp=new Node(); // create a new node
    temp->entropy = ent;
    temp->parent=NULL;
    temp->attrib_index=max;
    used_array[max]=1;
    if (root==NULL)
    {
        root=temp;
    }
    buildTreeRecursively(ent,max,root,used_array,valid_rows);

}
void TreeClass::initialValidator()
{
    for (int i=0; i<trainingList.size(); i++)
        valid_rows[i]=1;
    for (int i=0; i<6; i++)
        used_array[i]=0;


}
int main()
{
    ReadFromFile train;
    train.buildRecord("train.dat");
    train.getUnique();
    // train.displayList();
    TreeClass t;
    t.buildTree();
    return 0;
}
