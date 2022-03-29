#include <algorithm>
#include "chargingCurrentRangeCreator.h"

#define MAXIMUM_12_BIT_VALUE 4094
#define MAXIMUM_CUURENT_VALUE 10

int ConvertA2DToAmps(int ADCValue){
    int convertedAmps=round((((float)MAXIMUM_CUURENT_VALUE* (float)ADCValue) / (float)MAXIMUM_12_BIT_VALUE));
    return convertedAmps;
}

bool isChargingCurrentMeasurementListValid(chargingCurrentMeasurementList currentMeasurementList) {
    for(chargingCurrentMeasurementList::iterator rangeIterator = currentMeasurementList.begin(); rangeIterator != currentMeasurementList.end(); rangeIterator++){
        if(!(*rangeIterator > 0))
        {
            return false;
        }
    }
   return true;
}
string formatCurrentRangeString(int lowerRange, int upperRange) {
    return (to_string(lowerRange) + "-" + to_string(upperRange));
}

bool isGivenReadingsContinous(int lowerRange, int upperRange) {
    return((upperRange - lowerRange) <= 1);
}

currentRangeListWithReadings getRangeWithSingleReading(int chargingCurrentValue){
    currentRangeListWithReadings currentRangeList;
    currentRangeList.insert({formatCurrentRangeString(chargingCurrentValue,chargingCurrentValue),1});
    return currentRangeList;
}

currentRangeListWithReadings getRangeWithMultipleReading(chargingCurrentMeasurementList currentMeasurementList){
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
    currentRangeListWithReadings chargingCurrentReadingList;
    
    if((isChargingCurrentMeasurementListValid(currentMeasurementList)) && (currentMeasurementList.size() != 0)){
    sort(currentMeasurementList.begin(),currentMeasurementList.end());    
    if(currentMeasurementList.size() == 1) {
       return getRangeWithSingleReading(currentMeasurementList[0]);
    }
         return getRangeWithMultipleReading(currentMeasurementList);
    }
    return chargingCurrentReadingList;
}
