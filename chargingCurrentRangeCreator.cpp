#include <algorithm>
#include "chargingCurrentRangeCreator.h"

string formatCurrentRangeString(int lowerRange, int upperRange) {
    return (to_string(lowerRange) + "-" + to_string(upperRange));
}

bool isGivenReadingsContinous(int lowerRange, int upperRange) {
    return((upperRange - lowerRange) <= 1);
}

currentRangeListWithReadings getRangeWithSingleReading(int chargingCurrentValue)
{
    currentRangeListWithReadings currentRangeList;
    currentRangeList.insert({formatCurrentRangeString(chargingCurrentValue,chargingCurrentValue),1});
    return currentRangeList;
}

currentRangeListWithReadings getRangeWithMultipleReading(chargingCurrentMeasurementList currentMeasurementList)
{
    chargingCurrentMeasurementList continuousCurrentRangeList;
    currentRangeListWithReadings chargingCurrentReadingList;
    for(chargingCurrentMeasurementList::iterator rangeIterator = currentMeasurementList.begin(); rangeIterator != currentMeasurementList.end()-1; rangeIterator++) {
        continuousCurrentRangeList.push_back(*rangeIterator);
        chargingCurrentMeasurementList::iterator followingIterator=rangeIterator;
        followingIterator++;
         if(!isGivenReadingsContinous(*rangeIterator, *followingIterator)) {
            chargingCurrentReadingList.insert({formatCurrentRangeString(continuousCurrentRangeList.front(), continuousCurrentRangeList.back()),continuousCurrentRangeList.size()});
            continuousCurrentRangeList.clear();
        }
    }
    continuousCurrentRangeList.push_back(currentMeasurementList.back());
    chargingCurrentReadingList.insert({formatCurrentRangeString(continuousCurrentRangeList.front(), continuousCurrentRangeList.back()),continuousCurrentRangeList.size()});
    
    return chargingCurrentReadingList;
}

currentRangeListWithReadings getCurrentReadingsFromRanges(chargingCurrentMeasurementList & currentMeasurementList){
    sort(currentMeasurementList.begin(),currentMeasurementList.end());
    
    if(currentMeasurementList.size() == 1) {
       return getRangeWithSingleReading(currentMeasurementList[0]);
    }
    
    currentRangeListWithReadings chargingCurrentReadingList;
    if(currentMeasurementList.size() != 0)
    {
        chargingCurrentReadingList=getRangeWithMultipleReading(currentMeasurementList);
    }
    return chargingCurrentReadingList;
}
