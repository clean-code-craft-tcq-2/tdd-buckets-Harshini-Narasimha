#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "chargingCurrentRangeCreator.h"

TEST_CASE("Output the number of readings where the current measurements have 2 continuous current charging data") {
  std::vector<int> chargingCurrentSampleList = {4,5};
  std::map<std::string, int> expectedOutputRange = {{"4-5",2}};
  REQUIRE(getCurrentReadingsFromRanges(chargingCurrentSampleList) == expectedOutputRange);
}

TEST_CASE("Range list emoty when no reading available") {
  std::vector<int> emptyChargingCurrentSampleList;
  std::map<std::string, int> expectedEmptyOutputRange;
  REQUIRE(getCurrentReadingsFromRanges(emptyChargingCurrentSampleList) == expectedEmptyOutputRange);
}

TEST_CASE("Output the number of readings where the current measurements have 1 current charging data") {
  std::vector<int> chargingCurrentSampleList = {4};
  std::map<std::string, int> expectedOutputRange = {{"4-4",1}};
  REQUIRE(getCurrentReadingsFromRanges(chargingCurrentSampleList) == expectedOutputRange);
}
  
TEST_CASE("Output the number of readings where the current measurements have multiple current charging data") {
  std::vector<int> chargingCurrentSampleList = {5,4,5,9,10,11,12,13};
  std::map<std::string, int> expectedOutputRange = {{"4-5",3},{"9-13",5}};
  REQUIRE(getCurrentReadingsFromRanges(chargingCurrentSampleList) == expectedOutputRange);
}

TEST_CASE("Get the Reading for list with single entry") {
  std::map<std::string, int> expectedOutputRange = {{"7-7",1}};
  REQUIRE(getRangeWithSingleReading(7) == expectedOutputRange);
}

TEST_CASE("Get the Reading for list with multiple entry") {
  std::vector<int> chargingCurrentSampleList = {4,7,10};
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
