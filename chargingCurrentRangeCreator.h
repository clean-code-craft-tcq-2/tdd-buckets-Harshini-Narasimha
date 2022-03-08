#include <iostream>
#include <vector>
#include <map>
using namespace std;

typedef map<string, int> currentRangeListWithReadings;
typedef vector<int> chargingCurrentMeasurementList;

string formatCurrentRangeString(int lowerRange, int upperRange);
currentRangeListWithReadings getRangeWithSingleReading(int chargingCurrentValue);
currentRangeListWithReadings getRangeWithMultipleReading(chargingCurrentMeasurementList currentMeasurementList);
currentRangeListWithReadings getCurrentReadingsFromRanges(chargingCurrentMeasurementList & currentMeasurementList);
