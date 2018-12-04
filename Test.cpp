#include <iostream>
#include <cmath>
using namespace std;


int convertOutPut(int numerator, int denominator);
int *ifProper(string fraction);
int *ifMixed(string fractionInput);
int numStringToInt(string numString);
string sliceTheString(int previous, int next, string partOfFraction, string Fraction);
int findLength(string fractionInput);
int GCF(int input1, int input2);
int checkIfMixed(string fractionInput);



int main(){

    string fractionInput1, fractionInput2;
    cout<<"Enter number 1: ";
    cin>>fractionInput1;
    cout<<"Enter number 2: ";
    cin >> fractionInput2;
    int *fractionInput1Array = nullptr;
    int*fractionInput2Array = nullptr;
    if(checkIfMixed(fractionInput1)){
        fractionInput1Array = ifMixed(fractionInput1);
    }
    else{
        fractionInput1Array = ifProper(fractionInput1);
    }
    if(checkIfMixed(fractionInput2)){
        fractionInput2Array = ifMixed(fractionInput2);
    }
    else{
        fractionInput2Array = ifProper(fractionInput2);
    }
    int newNumerator, newDenominator;
    newNumerator = fractionInput1Array[0]*fractionInput2Array[1]+fractionInput1Array[1]*fractionInput2Array[0];
    newDenominator = fractionInput1Array[1]*fractionInput2Array[1];
    convertOutPut(newNumerator,newDenominator);

    delete[]fractionInput1Array;
    delete[]fractionInput2Array;
}

//////////////////////////////////////////////////////
// Checks if the string is a mixed fraction type or //
// proper fraction by looking for the parenthesis   //
// in the format given.                             //
//////////////////////////////////////////////////////

int checkIfMixed(string fractionInput){
    for(int i=0 ; i<findLength(fractionInput); i++){
       if(fractionInput[i] == '('){
            return 1;
          }
    }
    return 0;

}

////////////////////////////////////////////////////
// Uses the recursive algorithm to calculate the  //
// GCD of two terms.                              //
////////////////////////////////////////////////////

int GCF( int x, int y )
{
   if( x < y )
      return GCF( y, x );


   if( y == 0 )
     return x;
   else
      return GCF( y, x%y );
}

//////////////////////////////////////////////////
// Used to find the length of the sting without //
// using .length() method.                      //
//////////////////////////////////////////////////

int findLength(string fractionInput){
    int i = 0;
    while(fractionInput[i]){
        i++;
    }
    return i;
}

///////////////////////////////////////////////////////////
// This function takes four inputs which are used to cut //
// the sting into the places wanted so and return the    //
// sliced string to the another function so that it can  //
// be changed to int.                                    //
///////////////////////////////////////////////////////////

string sliceTheString(int previous, int next, string partOfFraction, string Fraction){
    for(previous;previous<next;previous++){
        partOfFraction+= Fraction[previous];
    }
    return partOfFraction;
}

///////////////////////////////////////////
// Changes string of numbers to integers //
//////////////////////////////////////////

int numStringToInt(string numString){
    int lenOfString = findLength(numString)-1;
    int finalNum=0;
    for(int i=0;i<=lenOfString; i++){
        int convertedToInt;
        convertedToInt = numString[i]-'0';
        finalNum +=(convertedToInt*pow(10,lenOfString-i));
    }
    return finalNum;
}

///////////////////////////////////////////////
// If one of the inputs is a Mixed fraction  //
// this faction will take and manipulate it  //
// and return an array of the numerator and  //
// denominator.                              //
///////////////////////////////////////////////

int *ifMixed(string fractionInput){
    string wholeNum, numerator, denominator;
    int valueCounter = 0;
    int previous = 0;
    int lenn = findLength(fractionInput);
    for(int i = 0; i<lenn; i++){
        if((fractionInput[i]=='(')||(fractionInput[i]=='/')||(fractionInput[i]==')')){
            switch (valueCounter){
                case(0):
                    wholeNum = sliceTheString(previous,i, wholeNum,fractionInput);
                    valueCounter++;
                    previous=i;
                    break;
                case(1):
                    numerator = sliceTheString(previous+1,i, numerator,fractionInput);
                    valueCounter++;
                    previous=i;
                    break;
                case(2):
                    denominator = sliceTheString(previous+1,i, denominator,fractionInput);
                    previous=i;
                    break;
                default:
                    cout<<"User Input Error";
                    return 0;
            }

        }

        }
        int *fractionArray = nullptr;
        fractionArray = new int[2];
        fractionArray[1] = numStringToInt(denominator);
        fractionArray[0] = numStringToInt(wholeNum)*fractionArray[1] + numStringToInt(numerator);
        return fractionArray;


}

///////////////////////////////////////////////
// If one of the inputs is a PROPER fraction //
// this faction will take and manipulate it  //
// and return an array of the numerator and  //
// denominator.                              //
///////////////////////////////////////////////

int *ifProper(string fraction){
    int previous = 0;
    string numerator, denominator;
    for(int i=0; i< findLength(fraction);i++){

        if(fraction[i]=='/'){
            numerator = sliceTheString(previous,i,numerator, fraction);
            denominator = sliceTheString(i+1,findLength(fraction), denominator, fraction);
            break;
        }
    }
    int *fractionArray2 = nullptr;
    fractionArray2 = new int[2];
    fractionArray2[1] = numStringToInt(denominator);
    fractionArray2[0]= numStringToInt(numerator);
    return fractionArray2;

}

/////////////////////////////////////////////////////
// This Function Takes the final numerator and     //
//denominator and converts it to Mixed or proper   //
//fraction                                         //
/////////////////////////////////////////////////////

int convertOutPut(int numerator, int denominator){

    int factor = GCF(numerator, denominator);
    numerator = numerator/factor;
    denominator = denominator/factor;
    int preceedingValue = numerator/denominator;
    int remainder = numerator%denominator;

    if(preceedingValue==0 || remainder == 0){
       cout <<numerator<<"/"<<denominator<< endl;
    }
    else{


        cout<< preceedingValue << "("<<remainder<< "/"<< denominator << ")"<< endl;
    }

}

