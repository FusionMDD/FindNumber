#include <iostream>
#include <map>
#include <vector>
#include <chrono>

using namespace std;

const int NUMBER_LENGTH = 4;
int positionFunctionCounter = 0;
int countFunctionCounter = 0;

int checkPosition (vector <int> number, vector <int> guessNumber)//function to check count of numbers with normal position
{
    int counter = 0;

    ++positionFunctionCounter;

    for (auto i=0; i<NUMBER_LENGTH; ++i)
    {
        if (number[i] == guessNumber[i])
        {
            ++counter;
        }
    }
    return counter;
}

int checkCount (vector <int> number, vector <int> guessNumber)//function to check count of numbers with normal value
{
    int counter = 0;
    map <int,int> numbersCounter;
    ++countFunctionCounter;

    for (auto i=0; i<NUMBER_LENGTH; ++i)
    {
        ++numbersCounter[guessNumber[i]];
    }

    for (auto i=0; i<NUMBER_LENGTH; ++i)
    {
        if(numbersCounter[number[i]]-1 > -1)
        {
            --numbersCounter[number[i]];
            ++counter;
        }
    }

    return counter;
}

vector<int> splitNumbers(int number)//function witch return array of separate numbers
{
    vector <int> guessArray (NUMBER_LENGTH);

    for (auto i=3; i>= 0; --i)
    {
        guessArray[i] = number % 10;
        number /= 10;
    }

    return guessArray;
}

vector <int> findCombination(vector<int> numArray, int samePositionCount,vector<int> guessNumber)// function witch looking for right combination
{
    for (auto i=0; i<NUMBER_LENGTH; ++i)
    {
        for(auto j=i; j<NUMBER_LENGTH; ++j)
        {
            if(i != j)
            {
                swap(numArray[i], numArray[j]);

                if(!(checkPosition(guessNumber, numArray) > samePositionCount))
                {
                    swap(numArray[i], numArray[j]);
                }
                else
                {
                    ++samePositionCount;
                    break;
                }
            }
        }
        if(samePositionCount == NUMBER_LENGTH)
        {
            break;
        }
    }
    return numArray;
}

int guessNumber(int number)
{
    int res=0;
    vector<int> guessNumber = splitNumbers(number);
    vector<int> result (NUMBER_LENGTH);

    int samePositionCount=checkPosition(guessNumber, result);

    int sameNumbersCount=checkCount(guessNumber, result);

    if (sameNumbersCount != NUMBER_LENGTH)
    {
        for (auto i=1; i<10; ++i)
        {
            for (int j=sameNumbersCount; j<NUMBER_LENGTH; ++j)
            {
                result[j] = i;
            }
            sameNumbersCount=checkCount(guessNumber, result);
        }
    }

    if (sameNumbersCount == NUMBER_LENGTH)
    {
        while (samePositionCount != NUMBER_LENGTH)
        {
            result = findCombination(result, samePositionCount, guessNumber);

            samePositionCount = checkPosition(guessNumber, result);
        }
    }

    //    for(auto i=0;i<NUMBER_LENGTH;i++)
    //    {
    //        cout<<result[i];
    //    }
    //    cout<<endl;

    res=result[0];

    for(int i=1; i<4; ++i)
    {
        res=res * 10 + result[i];
    }

    return res;
}

int main()
{
    chrono::microseconds maxTime=std::chrono::microseconds(0);
    chrono::microseconds minTime=std::chrono::microseconds(1000000);
    int worstNumber = 0;
    int maxCallPositionCheckFunction=0;
    int minCallPositionCheckFunction=99999999999;
    int maxCallCountCheckFunction=0;
    int minCallCountCheckFunction=99999999999;

    for (int i=0; i<1000; ++i)
    {
        auto start = chrono::high_resolution_clock::now();

        if(i != guessNumber(i))
        {
            cout<<"Error for "<<i<<endl;
        }

        auto stop =chrono::high_resolution_clock::now();
        std::chrono::duration<long, std::micro> duration= chrono::duration_cast<chrono::microseconds>(stop - start);

        if (duration > maxTime)
        {
            maxTime = duration;
            worstNumber = i;
        }

        if (duration < minTime)
        {
            minTime = duration;
        }

        if (positionFunctionCounter > maxCallPositionCheckFunction)
        {
            maxCallPositionCheckFunction = positionFunctionCounter;
        }

        if (positionFunctionCounter < minCallPositionCheckFunction)
        {
            minCallPositionCheckFunction = positionFunctionCounter;
        }

        if (countFunctionCounter > maxCallCountCheckFunction)
        {
            maxCallCountCheckFunction = countFunctionCounter;
        }

        if (countFunctionCounter < minCallCountCheckFunction)
        {
            minCallCountCheckFunction = countFunctionCounter;
        }

        positionFunctionCounter = 0;
        countFunctionCounter = 0;
    }

    cout<<"MinTime "<<minTime.count()<<" microseconds"<<endl<<"MaxTime "<<maxTime.count()<<" microseconds"<<endl<<"Worst number by speed is "<<worstNumber<<endl;
    cout<<"Minimum call of position function is "<<minCallPositionCheckFunction<<endl;
    cout<<"Maximum call of position function is "<<maxCallPositionCheckFunction<<endl;
    cout<<"Minimum call of count function is "<<minCallCountCheckFunction<<endl;
    cout<<"Maximum call of count function is "<<maxCallCountCheckFunction<<endl;

    return 0;
}
