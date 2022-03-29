#include <algorithm>
#include "chargingCurrentRangeCreator.h"
#include <math.h>

#define MAXIMUM_12_BIT_VALUE 4094
#define MAXIMUM_CUURENT_VALUE 10

int ConvertA2DToAmps(int ADCValue){
    int convertedAmps=round((((float)MAXIMUM_CUURENT_VALUE* (float)ADCValue) / (float)MAXIMUM_12_BIT_VALUE));
    return convertedAmps;
}

chargingCurrentMeasurementList getConvertedAmpsList(const chargingCurrentMeasurementList A2D12BitConverterList)
{
    std::vector convertedAmpsList;
    for(int inputIndex=0; inputIndex < A2D12BitConverterList.size(); inputIndex++)
    {
       convertedAmpsList.push_back(convertA2DToAmps(A2D12BitConverterList[inputIndex]));
    }
    return convertedAmpsList;
}

bool isChargingCurrentMeasurementListValid(chargingCurrentMeasurementList currentMeasurementList) {
    for(chargingCurrentMeasurementList::iterator rangeIterator = currentMeasurementList.begin(); rangeIterator != currentMeasurementList.end(); rangeIterator++){
        if((*rangeIterator < 0) || (*rangeIterator>MAXIMUM_12_BIT_VALUE))
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

currentRangeListWithReadings getCurrentReadingsFromRanges(const chargingCurrentMeasurementList & currentMeasurementList){
    currentRangeListWithReadings chargingCurrentReadingList;
    
    if((isChargingCurrentMeasurementListValid(currentMeasurementList)) && (currentMeasurementList.size() != 0)){
    chargingCurrentMeasurementList convertedAmpsList=getConvertedAmpsList(currentMeasurementList);
    sort(convertedAmpsList.begin(),convertedAmpsList.end());    
    if(convertedAmpsList.size() == 1) {
       return getRangeWithSingleReading(convertedAmpsList[0]);
    }
         return getRangeWithMultipleReading(convertedAmpsList);
    }
    return chargingCurrentReadingList;
}
