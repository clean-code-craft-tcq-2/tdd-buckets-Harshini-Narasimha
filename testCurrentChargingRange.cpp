#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "chargingCurrentRangeCreator.h"

TEST_CASE("Check input list validity where one of the data is invalid") {
  SECTION("Check For input validity where one of the value is negative")
  {
     std::vector<int> chargingCurrentSampleList={100,200,-4,700,800};
     REQUIRE(isChargingCurrentMeasurementListValid(chargingCurrentSampleList)==false);
  }
  SECTION("Check For input validity where one of the value is greater than 4094")
  {
     std::vector<int> chargingCurrentSamples={1067,2,4099,789,800};
     REQUIRE(isChargingCurrentMeasurementListValid(chargingCurrentSamples)==false);
  }
}

TEST_CASE("Check input list validity") {
  std::vector<int> chargingCurrentSampleList={1,2,4,7,8,9,1};
  REQUIRE(isChargingCurrentMeasurementListValid(chargingCurrentSampleList)==true);
}
TEST_CASE("Output the number of readings where the current measurements have 2 continuous current charging data") {
  std::vector<int> chargingCurrentSampleList = {4,5};
  std::map<std::string, int> expectedOutputRange = {{"4-5",2}};
  REQUIRE(getCurrentReadingsFromRanges(chargingCurrentSampleList) == expectedOutputRange);
}

TEST_CASE("Range list empty when no reading available") {
  std::vector<int> emptyChargingCurrentSampleList;
  std::map<std::string, int> expectedEmptyOutputRange;
  REQUIRE(getCurrentReadingsFromRanges(emptyChargingCurrentSampleList) == expectedEmptyOutputRange);
}

TEST_CASE("Output the number of readings where the current measurements have 1 current charging data") {
  std::vector<int> chargingCurrentSampleList = {1546};
  std::map<std::string, int> expectedOutputRange = {{"4-4",1}};
  REQUIRE(getCurrentReadingsFromRanges(chargingCurrentSampleList) == expectedOutputRange);
}
  
TEST_CASE("Output the number of readings where the current measurements have multiple current charging data") {
  std::vector<int> chargingCurrentSampleList = {1846,1546,1946,3000,3400,3500,4094};
  std::map<std::string, int> expectedOutputRange = {{"4-5",3},{"7-10",4}};
  REQUIRE(getCurrentReadingsFromRanges(chargingCurrentSampleList) == expectedOutputRange);
}

TEST_CASE("Get the Reading for list with discontinuous entry") {
  std::map<std::string, int> expectedOutputRange = {{"7-7",1}};
  REQUIRE(getRangeWithSingleReading(7) == expectedOutputRange);
}

TEST_CASE("Get the Reading for list with multiple entry") {
  std::vector<int> chargingCurrentSampleList = {1546,3000,4092};
  std::map<std::string, int> expectedOutputRange = {{"4-4",1},{"7-7",1},{"10-10",1}};
  REQUIRE(getCurrentReadingsFromRanges(chargingCurrentSampleList) == expectedOutputRange);
}

TEST_CASE("Format the range in lowerRange-upperRange format") {
  string expectedStringFormat ="7-10";
  REQUIRE(formatCurrentRangeString(7,10) == expectedStringFormat);
}

TEST_CASE("Check if given values are continuous") {
  REQUIRE(isGivenReadingsContinous(7,10) == false);
  REQUIRE(isGivenReadingsContinous(7,8) == true);
}

TEST_CASE("Check the conversion of 12-bit value to Amps") {
  SECTION("Check For 12-bit value 0")
  {
    REQUIRE(ConvertA2DToAmps(0) == 0);
  }
  SECTION("Check For 12-bit value 4095")
  {
    REQUIRE(ConvertA2DToAmps(4095) == 10);
  }
  SECTION("Check For 12-bit value 1146")
  {
    REQUIRE(ConvertA2DToAmps(1146) == 3);
  }
}

TEST_CASE("Check the converetd list from 12-bit value to Amps") {
  std::vector<int> inputList={1546,3000,4092};
  std::vector<int> convertedList=getConvertedAmpsList(inputList);
  std::vector<int> expectedList={4,7,10};
  REQUIRE(convertedList == expectedList);
}
