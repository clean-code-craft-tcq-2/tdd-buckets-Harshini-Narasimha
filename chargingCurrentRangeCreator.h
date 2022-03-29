#include <iostream>
#include <vector>
#include <map>
using namespace std;

typedef map<string, int> currentRangeListWithReadings;
typedef vector<int> chargingCurrentMeasurementList;

string formatCurrentRangeString(int lowerRange, int upperRange);
bool isGivenReadingsContinous(int lowerRange, int upperRange);
currentRangeListWithReadings getRangeWithSingleReading(int chargingCurrentValue);
currentRangeListWithReadings getRangeWithMultipleReading(chargingCurrentMeasurementList currentMeasurementList);
currentRangeListWithReadings getCurrentReadingsFromRanges(const chargingCurrentMeasurementList & currentMeasurementList);
bool isChargingCurrentMeasurementListValid(chargingCurrentMeasurementList currentMeasurementList);
int convertA2DToAmps(int ADCValue);
chargingCurrentMeasurementList getConvertedAmpsList(const chargingCurrentMeasurementList A2D12BitConverterList);
