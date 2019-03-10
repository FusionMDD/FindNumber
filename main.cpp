#include <iostream>
#include <map>
#include <vector>

using namespace std;

int checkPosition (vector <int> number, vector <int> guessNumber)//function to check count of numbers with normal position
{
    int counter = 0;

    for (auto i=0; i<4; i++)
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

    for (auto i=0;i<4;i++)
    {
        ++numbersCounter[guessNumber[i]];
    }

    for (auto i=0; i<4; i++)
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
    vector <int> guessArray (4);

    for (auto i=3; i>= 0; i--)
    {
        guessArray[i] = number % 10;
        number /= 10;
    }

    return guessArray;
}

vector <int> findCombination(vector<int> numArray, int samePositionCount,vector<int> guessNumber)// function witch looking for right combination
{
    for (auto i=0; i<4; i++)
    {
        for(auto j=i; j<4; j++)
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
        if(samePositionCount == 4)
        {
            break;
        }
    }
    return numArray;
}

void guessNumber(int number)
{
    vector<int> guessNumber = splitNumbers(number);
    vector<int> result (4);

    int samePositionCount=checkPosition(guessNumber, result);

    int sameNumbersCount=checkCount(guessNumber, result);

    if (sameNumbersCount != 4)
    {
        for (auto i=0; i<4; i++)
        {
            int tmp = result[i];

            for(auto j=0; j<10; j++)
            {
                result[i] = j;

                if (checkCount(guessNumber, result)>sameNumbersCount)
                {
                    tmp=result[i];
                    ++sameNumbersCount;
                    break;
                }
            }
            result[i] = tmp;
            if(sameNumbersCount == 4)
            {
                break;
            }
        }
    }

    if (sameNumbersCount == 4)
    {
        while (samePositionCount != 4)
        {
            result = findCombination(result, samePositionCount, guessNumber);

            samePositionCount = checkPosition(guessNumber, result);
        }
    }

    for(auto i=0;i<4;i++)
    {
        cout<<result[i];
    }
}

int main()
{
    int number;

    cout << "Please input 4 digit number" << endl;
    cin>>number;

    guessNumber(number);

    return 0;
}
